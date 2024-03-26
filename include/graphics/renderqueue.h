#pragma once

#include "core/object.h"
#include <map>
#include <memory>

class RenderQueue
{
public:
    void SetPass(int pass);
    void UnsetPass();
    void Add(std::shared_ptr<Object>, float position = 0.0f);
    void Remove(std::shared_ptr<Object>);
    void Draw();
    static void RenderAll();
private:
    std::multimap<float, std::shared_ptr<Object>> objects;
public:
    std::shared_ptr<Camera2D> camera2d = nullptr;
    
};

