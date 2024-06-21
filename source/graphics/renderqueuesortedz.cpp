#include "core/object.h"
#include "graphics/renderqueuesortedz.h"

#include <algorithm>

static bool compareByZ(const std::weak_ptr<GeoObject> a, const std::weak_ptr<GeoObject> b)
{
    auto c = a.lock();
    auto d = b.lock();
    if(c == nullptr || d == nullptr) return false;
    if(c->GetPos() == nullptr || d->GetPos() == nullptr) return false;
    return c->GetPos()->world.position.z < d->GetPos()->world.position.z;
}

void RenderQueueSortedZ::PreRender()
{
    if(std::is_sorted(objects.begin(), objects.end(), compareByZ)) return;
    std::sort(objects.begin(), objects.end(), compareByZ);
}

void RenderQueueSortedZ::PostRender()
{
    
}