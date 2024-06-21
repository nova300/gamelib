#pragma once
#include <cstddef>
#include <vector>
#include <memory>

#include "core/objectstore.h"
#include "graphics/renderqueue.h"
#include "core/object.h"
#include "core/position.h"

#include <memory>

enum RenderQueueTypes
{
    RQ_NULL,
    RQ_SPRITES,
    RQ_VIRTUAL,
    RQ_3D,
    RQ_MENU,
    RQ_CUSTOM
};

class ProgramStack;

class Program
{
    friend class ProgramStack;
public:
    virtual ~Program() {};
    Program()
    {
        root.program = this;
    };
    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void PostUpdate(float deltaTime) {};
    virtual void Render() {};
    virtual void SoftRender() {};
    virtual void Destroy() {};
    virtual void Sleep() {};
    virtual void Wake() {};
    virtual void ConstantUpdate(float deltaTime) {};

    virtual RenderQueue* GetRenderQueue(int index) { return nullptr; };

    virtual bool FadeIn() {return true;}
    virtual bool FadeOut() {return true;}
    
    ProgramStack* GetStack();
private:
    ProgramStack* stack = NULL;
protected:
    Object root;
};