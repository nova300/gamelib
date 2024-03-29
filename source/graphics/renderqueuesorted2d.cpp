#include "core/object.h"
#include "graphics/renderqueuesorted2d.h"

#include <algorithm>
#include <raylib.h>

static bool compareByZ(const Object *a, const Object *b)
{
    return a->position.translation.z < b->position.translation.z;
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