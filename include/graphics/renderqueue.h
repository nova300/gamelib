#pragma once

#include <vector>
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
    void Add(Object* obj);
    void Remove(Object *obj);
    virtual void Render();
    static void RenderAll();

    virtual void PreRender() {};
    virtual void PostRender() {};
protected:
    int pass = 0;
    std::vector<Object*> objects;
};

