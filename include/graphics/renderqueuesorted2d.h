#pragma once

#include "graphics/renderqueue.h"

class RenderQueueSorted2D : public RenderQueue
{
public:
    RenderQueueSorted2D(Camera2D* CAM, int pass = 0) : RenderQueue(pass) , camera(CAM) {};
    void PreRender() override;
    void PostRender() override;
    Camera2D* camera = nullptr;
};