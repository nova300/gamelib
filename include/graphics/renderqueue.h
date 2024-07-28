#pragma once

#include <vector>
#include <raylib.h>

#include <memory>

#include "graphics/geoobject.h"
#include "utils/containers.h"



class RenderQueue
{
public:
    virtual void AddRender(std::shared_ptr<GeoObject> obj) = 0;
    virtual void RemoveRender(std::shared_ptr<GeoObject> obj) = 0;
    virtual void DrawRender() = 0;

    virtual void PreRender() = 0;
    virtual void PostRender() = 0;
};

class RenderQueueVector : public RenderQueue
{
public:
    virtual void AddRender(std::shared_ptr<GeoObject> obj) override;
    virtual void RemoveRender(std::shared_ptr<GeoObject> obj) override;
    virtual void DrawRender() override;

    virtual void PreRender() {};
    virtual void PostRender() {};
protected:
    std::vector<std::weak_ptr<GeoObject>> objects;
};

class RenderQueueMap2D : public RenderQueue
{
public:
    virtual void AddRender(std::shared_ptr<GeoObject> obj) override;
    virtual void RemoveRender(std::shared_ptr<GeoObject> obj) override;
    virtual void DrawRender() override;

    virtual void PreListGen() {};
    virtual void PreRender() {};
    virtual void PostRender() {};

    struct Node 
    {
        std::weak_ptr<GeoObject> object;
        bool occluded;
    };

public:
    IntRectangle renderBounds;
    Map2D<Node> objects;
    std::map<GeoObject*, int> indicies;
    std::vector<Node*> frameList;
};

class RenderQueueMap2DCam : public RenderQueueMap2D
{
public:
    RenderQueueMap2DCam(Camera2D* CAM) : camera(CAM) {};
    void PreListGen() override;
    void PreRender() override;
    void PostRender() override;
    Camera2D* camera = nullptr;
};