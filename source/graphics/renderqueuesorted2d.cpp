#include "core/object.h"
#include "graphics/renderqueuesorted2d.h"

#include <algorithm>
#include <raylib.h>

#include "utils/math.h"

bool RenderQueueSorted2D::compareByZ(const std::weak_ptr<GeoObject> a, const std::weak_ptr<GeoObject> b)
{
    auto c = a.lock();
    auto d = b.lock();
    if(c == nullptr || d == nullptr) return false;
    if(c->GetPos() == nullptr || d->GetPos() == nullptr) return false;
    return c->GetPos()->world.position.y + (c->GetPos()->world.size.y * c->GetPos()->world.scale.y) < d->GetPos()->world.position.y + (d->GetPos()->world.size.y * d->GetPos()->world.scale.y); 
}

void RenderQueueSorted2D::PreRender()
{
    if(!std::is_sorted(objects.begin(), objects.end(), compareByZ)) std::sort(objects.begin(), objects.end(), compareByZ);

    const Vector2 pos = GetScreenToWorld2D(Vector2Zero(), *camera);
    const Vector2 size = GetScreenToWorld2D(Vector2{(float)GetScreenWidth(), (float)GetScreenHeight()}, *camera);
    const Rectangle cameraBoundsWorld =
    {
        pos.x,
        pos.y,
        size.x,
        size.y
    };

    for(auto& obj : objects)
    {
        if(obj.expired()) continue;
        obj.lock()->OnScreenCheck(cameraBoundsWorld);
    }
    BeginMode2D(*camera);
    
}

void RenderQueueSorted2D::PostRender()
{
    EndMode2D();
}

bool RenderQueueSortedMap2D::compareByZ(const RenderQueueMap2D::Node* a, const RenderQueueMap2D::Node* b)
{
    if(a == nullptr || b == nullptr) return false;
    auto c = a->object.lock(); 
    auto d = b->object.lock();
    if(c == nullptr || d == nullptr) return false;
    if(c->GetPos() == nullptr || d->GetPos() == nullptr) return false;
    return c->GetPos()->world.position.y + (c->GetPos()->world.size.y * c->GetPos()->world.scale.y) < d->GetPos()->world.position.y + (d->GetPos()->world.size.y * d->GetPos()->world.scale.y); 
}

void RenderQueueSortedMap2D::PreListGen()
{
    if(camera)
    {
        const float offset = 0.0f;
        auto newBounds = GetCameraBounds(*camera, offset);
        renderBounds = newBounds;
    }
    
}


void RenderQueueSortedMap2D::PreRender()
{
    if(!std::is_sorted(frameList.begin(), frameList.end(), compareByZ)) std::sort(frameList.begin(), frameList.end(), compareByZ);

    BeginMode2D(*camera);
    
}

void RenderQueueSortedMap2D::PostRender()
{
    EndMode2D();
}
