#pragma once

#include "graphics/renderqueue.h"

class RenderQueueSorted2D : public RenderQueue
{
public:
    RenderQueueSorted2D(Camera2D* CAM) : camera(CAM) {};
    void PreRender() override;
    void PostRender() override;
    Camera2D* camera = nullptr;
private:
    static bool compareByZ(const std::weak_ptr<GeoObject> a, const std::weak_ptr<GeoObject> b);
};