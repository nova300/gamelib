#pragma once

#include <vector>
#include <raylib.h>

#include <memory>

class Object;

class RenderQueue
{
public:

    void AddRender(std::shared_ptr<Object> obj);
    void RemoveRender(std::shared_ptr<Object> obj);
    virtual void DrawRender();

    virtual void PreRender() {};
    virtual void PostRender() {};
protected:
    //int pass = 0;
    std::vector<std::weak_ptr<Object>> objects;
};

