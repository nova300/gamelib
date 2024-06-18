#include "core/object.h"
#include "graphics/renderqueuesortedz.h"

#include <algorithm>

static bool compareByZ(const std::weak_ptr<Object> a, const std::weak_ptr<Object> b)
{
    auto c = a.lock();
    auto d = b.lock();
    if(c == nullptr || d == nullptr) return false;
    return c->position.z < d->position.z;
}

void RenderQueueSortedZ::PreRender()
{
    if(std::is_sorted(objects.begin(), objects.end(), compareByZ)) return;
    std::sort(objects.begin(), objects.end(), compareByZ);
}

void RenderQueueSortedZ::PostRender()
{
    
}