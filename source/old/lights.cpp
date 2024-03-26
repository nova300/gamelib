#include "graphics/lights.h"
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>

Lights::Lights(Rectangle BOUNDS)
{
    bounds = BOUNDS;
    lightMask = LoadRenderTexture(BOUNDS.width, BOUNDS.height);

}

std::shared_ptr<Lights::LightInfo> Lights::SetupLight(float radius, Color color)
{
    std::shared_ptr<Lights::LightInfo> newlight = std::make_shared<Lights::LightInfo>();
    newlight->mask = LoadRenderTexture(bounds.width, bounds.height);
    lights.push_back(newlight);
    newlight->DrawLightMask();
    return newlight;
}

std::shared_ptr<Lights::LightOccluder> Lights::SetupOccluder()
{
    std::shared_ptr<Lights::LightOccluder> newocc = std::make_shared<Lights::LightOccluder>();
    occluders.push_back(newocc);
    return newocc;
}

Lights::LightInfo::~LightInfo()
{
    if(IsRenderTextureReady(mask))
    {
        UnloadRenderTexture(mask);
    }
}

void Lights::LightInfo::Set(Vector2 POS)
{
    position = POS;
    dirty = true;
}

void Lights::LightOccluder::Set(Rectangle BOUNDS)
{
    bounds = BOUNDS;
    dirty = true;
}

void Lights::LightInfo::ComputeShadowVolumeForEdge(Vector2 sp, Vector2 ep)
{
    float extension = outerRadius*2;

    Vector2 spVector = Vector2Normalize(Vector2Subtract(sp, position));
    Vector2 spProjection = Vector2Add(sp, Vector2Scale(spVector, extension));

    Vector2 epVector = Vector2Normalize(Vector2Subtract(ep, position));
    Vector2 epProjection = Vector2Add(ep, Vector2Scale(epVector, extension));

    ShadowGeometry sg = {0};


    sg.vertices[0] = sp;
    sg.vertices[1] = ep;
    sg.vertices[2] = epProjection;
    sg.vertices[3] = spProjection;

    shadows.push_back(sg);
}

void Lights::LightInfo::DrawLightMask()
{
    // Use the light mask
    BeginTextureMode(mask);

        ClearBackground(WHITE);

        // Force the blend mode to only set the alpha of the destination
        rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MIN);
        rlSetBlendMode(BLEND_CUSTOM);

        // If we are valid, then draw the light radius to the alpha mask
        if (valid) DrawCircleGradient((int)position.x, (int)position.y, outerRadius, ColorAlpha(WHITE, 0), WHITE);
        
        rlDrawRenderBatchActive();

        // Cut out the shadows from the light radius by forcing the alpha to maximum
        rlSetBlendMode(BLEND_ALPHA);
        rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MAX);
        rlSetBlendMode(BLEND_CUSTOM);

        // Draw the shadows to the alpha mask
        for (auto shadow : shadows)
        {
            DrawTriangleFan(shadow.vertices, 4, WHITE);
        }

        rlDrawRenderBatchActive();
        
        // Go back to normal blend mode
        rlSetBlendMode(BLEND_ALPHA);

    EndTextureMode();
}


bool Lights::LightInfo::Update(std::vector<std::weak_ptr<LightOccluder>>& occluders, bool dirtyOccluders, Rectangle maskBounds)
{

    if(dirty)
    {
        dirty = false;
        active = CheckCollisionPointRec(position, maskBounds);
    }

    if(!active || (!dirty && !dirtyOccluders)) return false;

    

    dirty = false;
    valid = false;

    shadows.clear();

    for(auto o : occluders)
    {
        if(o.expired()) continue;
        auto box = o.lock();

        if(CheckCollisionPointRec(position, box->bounds)) return false;

        if(!CheckCollisionRecs(bounds, box->bounds)) continue;

        Vector2 sp = Vector2{box->bounds.x, box->bounds.y};
        Vector2 ep = Vector2{box->bounds.x + box->bounds.width, box->bounds.y};

        if(position.y > ep.y) ComputeShadowVolumeForEdge(sp, ep);

        //right
        sp = ep;
        ep.y += box->bounds.height;
        if(position.x < ep.x) ComputeShadowVolumeForEdge(sp, ep);

        //bottom
        sp = ep;
        ep.x -= box->bounds.width;
        if(position.y < ep.y) ComputeShadowVolumeForEdge(sp, ep);

        //left
        sp = ep;
        ep.y -= box->bounds.height;
        if(position.x > ep.x) ComputeShadowVolumeForEdge(sp, ep);

        //box
        ShadowGeometry b = {0};
        b.vertices[0] = Vector2{ box->bounds.x, box->bounds.y };
        b.vertices[1] = Vector2{ box->bounds.x, box->bounds.y + box->bounds.height };
        b.vertices[2] = Vector2{ box->bounds.x + box->bounds.width, box->bounds.y + box->bounds.height };
        b.vertices[3] = Vector2{ box->bounds.x + box->bounds.width, box->bounds.y };
        shadows.push_back(b);
    }

    valid = true;

    DrawLightMask();

    return true;

}

void Lights::Update(float deltaTime)
{
    bool dirtyLights = false;

    for(std::vector<std::weak_ptr<Lights::LightOccluder>>::iterator it = occluders.begin(); it != occluders.end();)
    {
	    if(it.base()->expired())
	    {
	    	it = occluders.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }

    for(std::vector<std::weak_ptr<Lights::LightInfo>>::iterator it = lights.begin(); it != lights.end();)
    {
	    if(it.base()->expired())
	    {
	    	it = lights.erase(it);
	    }
	    else
	    {
	    	it++;
	    }
    }

    for(auto o : occluders)
    {
        auto occ = o.lock();
        if(occ->dirty)
        {
            occ->active = CheckCollisionRecs(occ->bounds, bounds);
            occ->dirty = false;
            dirtyLights = true;
        } 
    }

    for(auto l : lights)
    {
        if(l.lock()->Update(occluders, dirtyLights, bounds)) dirtyLights = true;
    }

    if(dirtyLights)
    {
        BeginTextureMode(lightMask);
            ClearBackground(BLACK);
            rlSetBlendFactors(RLGL_SRC_ALPHA, RLGL_SRC_ALPHA, RLGL_MIN);
            rlSetBlendMode(BLEND_CUSTOM);

            for(auto l : lights)
            {
                auto light = l.lock();
                if(light->active) DrawTextureRec(light->mask.texture, Rectangle{ 0, 0, (float)LIGHTMASKWIDTH, -(float)LIGHTMASKHEIGHT }, Vector2Zero(), WHITE);
            }

            rlDrawRenderBatchActive();

            rlSetBlendMode(BLEND_ALPHA);
        EndTextureMode();
    }
}

void Lights::Render()
{
    DrawTexturePro(lightMask.texture, (Rectangle){ 0, 0, (float)bounds.width, -(float)bounds.height }, bounds, Vector2Zero(), 0.0f, WHITE);

    for(auto l : lights)
    {
        if(l.expired()) continue;
        auto light = l.lock();
        if(light->active) DrawCircle((int)light->position.x, (int)light->position.y, 10, WHITE);
    }

}