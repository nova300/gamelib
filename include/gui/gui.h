#pragma once
//gui common classes / functions

#include "graphics/renderqueue.h"
#include <memory>

class WindowManager : public RenderQueueVector
{
public:
    WindowManager() {};
    virtual ~WindowManager() {};

    virtual Vector2 GetMousePos() { return GetMousePosition(); }

    virtual void MouseInput(Vector2 mousePos);

    int max = 0;
    int min = 0;
};


//gui modules
#include "gui/window.h"