#pragma once
// gui window base class
#include "core/behaviour.h"
#include "core/object.h"
#include "core/program.h"
#include "graphics/geoobject.h"
#include "gui/gui.h"
#include <string>

class Window : public Behaviour, public GeoObject
{
public:
    Window() {};
    virtual ~Window() {};

    virtual void Init() override;
    virtual void Update(float deltaTime) override;

    virtual void DrawContent() {};
    virtual const char* GetWindowTitle() { return "WINDOW"; };

    virtual void Render() override;
    virtual Position* GetPos() override
    {
        return &GetObject()->position;
    }

    virtual void OnMouseInputActive(Vector2 mousePos) override;

    bool minimized = false;
    bool resizing = false;
    bool moving = false;
    bool mouseOn = false;
    Vector2 scroll = Vector2Zero();
    Vector2 contentSize = Vector2{140, 320};

    WindowManager* windowManager = nullptr;

protected:
    virtual int GetDefaultRenderQueue() override
    {
        return RQ_WINDOWS;
    }

};

//template for rguilayout export template
class GUILAYOUT_NAME_PASCALCASE : public Window
{
public:
    virtual ~GUILAYOUT_NAME_PASCALCASE() {};

};