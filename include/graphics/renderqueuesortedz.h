#pragma once

#include "graphics/renderqueue.h"

class RenderQueueSortedZ : public RenderQueue
{
public:
    void PreRender() override;
    void PostRender() override;
private:
    static bool compareByZ(const std::weak_ptr<GeoObject> a, const std::weak_ptr<GeoObject> b);
};