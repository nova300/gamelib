#include "core/object.h"
#include "graphics/renderqueuesorted2d.h"

#include <algorithm>
#include <raylib.h>

static bool compareByZ(const std::weak_ptr<Object> a, const std::weak_ptr<Object> b)
{
    auto c = a.lock();
    auto d = b.lock();
    if(c == nullptr || d == nullptr) return false;
    return c->position.z < d->position.z;
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