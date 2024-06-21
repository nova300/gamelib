#include "core/object.h"
#include "graphics/renderqueuesorted2d.h"

#include <algorithm>
#include <raylib.h>

static bool compareByZ(const std::weak_ptr<GeoObject> a, const std::weak_ptr<GeoObject> b)
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

    BeginMode2D(*camera);
    
}

void RenderQueueSorted2D::PostRender()
{
    EndMode2D();
}