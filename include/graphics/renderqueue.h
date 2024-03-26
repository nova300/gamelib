#pragma once

#include <map>
#include <memory>
#include <raylib.h>

class Object;

class RenderQueue
{
public:
    RenderQueue(int pass);
    RenderQueue() {};
    ~RenderQueue();
    void SetPass(int pass);
    void UnsetPass();
    void Add(std::shared_ptr<Object>, float position = 0.0f);
    void Remove(std::shared_ptr<Object>);
    void Draw();
    static void RenderAll();
private:
    std::multimap<float, std::weak_ptr<Object>> objects;
public:
    std::shared_ptr<Camera2D> camera2d = nullptr;
};

