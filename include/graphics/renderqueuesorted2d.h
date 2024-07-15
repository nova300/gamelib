#pragma once

#include "graphics/renderqueue.h"

class RenderQueueSorted2D : public RenderQueueVector
{
public:
    RenderQueueSorted2D(Camera2D* CAM) : camera(CAM) {};
    void PreRender() override;
    void PostRender() override;
    Camera2D* camera = nullptr;
private:
    static bool compareByZ(const std::weak_ptr<GeoObject> a, const std::weak_ptr<GeoObject> b);
};

class RenderQueueSortedMap2D : public RenderQueueMap2D
{
public:
    RenderQueueSortedMap2D(Camera2D* CAM) : camera(CAM) {};
    void PreListGen() override;
    void PreRender() override;
    void PostRender() override;
    Camera2D* camera = nullptr;
private:
    static bool compareByZ(const RenderQueueMap2D::Node* a, const RenderQueueMap2D::Node* b);
};