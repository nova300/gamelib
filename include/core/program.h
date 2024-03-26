#pragma once
#include <cstddef>
#include <vector>
#include <memory>


#include "graphics/renderqueue.h"
#include "core/object.h"
#include "core/position.h"


class ProgramStack;

class Program
{
    friend class ProgramStack;
public:
    virtual void Init() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Render() {};
    virtual void Destroy() {};
    virtual void Sleep() {};
    virtual void Wake() {};
    
    ProgramStack* GetStack();
    RenderQueue* GetQueue();

private:
    RenderQueue renderQueue;
    std::vector<std::shared_ptr<Object>> objects;
    ProgramStack* stack = NULL;
};