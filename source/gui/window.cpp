#include "gui/window.h"
#include <raygui.h>

#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
    #define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
    #define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

const static int close_title_size_delta_half = (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE);


void Window::Init()
{
    auto rq = GetObject()->GetProgram()->GetRenderQueue(RQ_WINDOWS);
    if(rq == nullptr) return;
    auto wm = dynamic_cast<WindowManager*>(rq);
    if(wm == nullptr) return;

    windowManager = wm;
    wm->AddRender(GetObject()->GetBehaviour<Window>().lock());
};

void Window::OnMouseInputActive(Vector2 mousePos)
{   
    mouseOn = true;
    auto *trans = &GetPos()->world;
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !moving && !resizing)
    {
        Rectangle tilebarCollider = Rectangle{
            trans->position.x, 
            trans->position.y, 
            trans->size.x - (RAYGUI_WINDOW_CLOSEBUTTON_SIZE + close_title_size_delta_half),
            RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT
        };

        Rectangle resizeCollider = Rectangle{
            trans->position.x + trans->size.x - 20,
            trans->position.y + trans->size.y - 20,
            20,
            20
        };

        if(CheckCollisionPointRec(mousePos, tilebarCollider))
        {
            moving = true;
        }
        else if (!minimized && CheckCollisionPointRec(mousePos, resizeCollider))
        {
            resizing = true;
        }
    }


}

void Window::Update(float deltaTime)
{
    auto *local = &GetPos()->local;
    if(moving)
    {
        Vector2 mouseDelta = GetMouseDelta();
        local->Translate(mouseDelta);

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            moving = false;
        }
    }
    else if(resizing)
    {
        Vector2 mouse = GetMousePosition();
        if(mouse.x > local->position.x) local->size.x = mouse.x - local->position.x;
        if(mouse.y > local->position.y) local->size.y = mouse.y - local->position.y;
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            resizing = false;
        }
    }
}

void Window::Render()
{
    auto *trans = &GetPos()->world; 
    if(minimized)
    {
        GuiStatusBar(Rectangle{trans->position.x, trans->position.y, trans->size.x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT}, GetWindowTitle());
        if(mouseOn && GuiButton(Rectangle{trans->position.x + trans->size.x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half, trans->position.y + close_title_size_delta_half, RAYGUI_WINDOW_CLOSEBUTTON_SIZE, RAYGUI_WINDOW_CLOSEBUTTON_SIZE}, "#120#"))
        {
            minimized = false;
        }
    }
    else
    {
        minimized = GuiWindowBox(Rectangle{trans->position.x, trans->position.y, trans->size.x, trans->size.y}, GetWindowTitle());
        minimized = minimized && mouseOn;
        //Rectangle 

        GuiDrawIcon(71, trans->position.x + trans->size.x - 20, trans->position.y + trans->size.y - 20, 1, BLACK);
    }

    mouseOn = false;
}

