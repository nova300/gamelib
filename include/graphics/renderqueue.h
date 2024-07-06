#pragma once

#include <vector>
#include <raylib.h>

#include <memory>

#include "graphics/geoobject.h"



class RenderQueue
{
public:

    void AddRender(std::shared_ptr<GeoObject> obj);
    void RemoveRender(std::shared_ptr<GeoObject> obj);
    virtual void DrawRender();

    virtual void PreRender() {};
    virtual void PostRender() {};
protected:
    //int pass = 0;
    std::vector<std::weak_ptr<GeoObject>> objects;
};