#include "core/object.h"
#include "graphics/renderqueuesortedz.h"

#include <algorithm>

static bool compareByZ(const Object *a, const Object *b)
{
    return a->position.z < b->position.z;
}

void RenderQueueSortedZ::PreRender()
{
    if(std::is_sorted(objects.begin(), objects.end(), compareByZ)) return;
    std::sort(objects.begin(), objects.end(), compareByZ);
}

void RenderQueueSortedZ::PostRender()
{
    
}