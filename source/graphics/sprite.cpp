#include "graphics/sprite.h"
#include "graphics/texturecache.h"
#include "core/object.h"
#include "graphics/renderqueue.h"
#include "core/program.h"

void Sprite::Init()
{
    RenderQueue* rq = GetObject()->GetProgram()->GetRenderQueue(RQ_SPRITES);
    rq->AddRender(GetObject()->GetBehaviour<Sprite>().lock());
}

void Sprite::Render()
{
    if(managed)
    {
        if(!IsTextureReady(texture->Texture())) return;
        auto pos = GetObject()->position.world;

        Rectangle dst = Rectangle{pos.position.x, pos.position.y, (float)pos.size.x * pos.scale.x, (float)pos.size.y * pos.scale.y};
        DrawTexturePro(texture->Texture(), src, dst, Vector2{0.0f, 0.0f}, pos.rotation.z, color);
    }
    else
    {
        if(!IsTextureReady(unmanagedTexture)) return;
        auto pos = GetObject()->position.world;

        Rectangle dst = Rectangle{pos.position.x, pos.position.y, (float)pos.size.x * pos.scale.x, (float)pos.size.y * pos.scale.y};
        DrawTexturePro(unmanagedTexture, src, dst, Vector2{0.0f, 0.0f}, pos.rotation.z, color);
    }

}

void Sprite::Load(std::string path)
{
    managed = true;
    texture = CLoadTexture(path);
    GetObject()->position.local.size.x = texture->Texture().width;
    GetObject()->position.local.size.y = texture->Texture().height;
    src = Rectangle{0.0f, 0.0f, (float)texture->Texture().width, (float)texture->Texture().height};
}

void Sprite::Load(std::shared_ptr<CTexture> tex)
{
    managed = true;
    texture = tex;
    GetObject()->position.local.size.x = texture->Texture().width;
    GetObject()->position.local.size.y = texture->Texture().height;
    src = Rectangle{0.0f, 0.0f, (float)texture->Texture().width, (float)texture->Texture().height};
}

void Sprite::Load(Texture2D tex)
{
    unmanagedTexture = tex;
    GetObject()->position.local.size.x = tex.width;
    GetObject()->position.local.size.y = tex.height;
    src = Rectangle{0.0f, 0.0f, (float)unmanagedTexture.width, (float)unmanagedTexture.height};
    managed = false;
}

void ColorRectangle::Init()
{
    RenderQueue* rq = GetObject()->GetProgram()->GetRenderQueue(RQ_SPRITES);
    rq->AddRender(GetObject()->GetBehaviour<ColorRectangle>().lock());
}

void ColorRectangle::Render()
{
    auto pos = GetObject()->position.world;
    DrawRectanglePro(pos.Rect(), Vector2Zero(), 0.0f, color);
}

void ColorCircle::Init()
{
    RenderQueue* rq = GetObject()->GetProgram()->GetRenderQueue(RQ_SPRITES);
    rq->AddRender(GetObject()->GetBehaviour<ColorCircle>().lock());
}

void ColorCircle::Render()
{
    auto pos = GetObject()->position.world;
    DrawCircleV(pos.Vec2(), pos.size.x, color);
}