#pragma once

#include <vector>
#include <raylib.h>

class Object;

class RenderQueue
{
public:
    //RenderQueue(int pass);
    //RenderQueue() {};
    //~RenderQueue();
    //void SetPass(int pass);
    //void UnsetPass();
    void AddRender(Object* obj);
    void RemoveRender(Object *obj);
    virtual void DrawRender();
    //static void RenderAll();

    virtual void PreRender() {};
    virtual void PostRender() {};
protected:
    //int pass = 0;
    std::vector<Object*> objects;
};

