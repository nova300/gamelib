#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <vector>
#include <deque>
#include "graphics.h"
#include "core/position.h"

class GeoObject
{
private:
    bool visible = true;
public:
    virtual void Render() = 0;
    virtual void OnMouseInputActive(Vector2 mousePos) {};
    virtual bool MouseInput(Vector2 mousePos)
    {
        auto pos = GetPos();
        if(pos == nullptr) return false;
        if(CheckCollisionPointRec(mousePos, pos->world.Rect()))
        {   
            OnMouseInputActive(mousePos);
            return true;
        }
        return false;
    }
    virtual bool OnScreenCheck(Rectangle screenRectWorld)
    {
        auto pos = GetPos();
        if(pos == nullptr)
        {
            visible = false;
            return false;
        }
        if(CheckCollisionRecs(screenRectWorld, pos->world.Rect()))
        {
            visible = true;
            return true;
        }
        visible = false;
        return false;
    }
    virtual bool OnScreenCheck(BoundingBox visibleBounds)
    {
        auto pos = GetPos();
        if(pos == nullptr)
        {
            visible = false;
            return false;
        }
        if(CheckCollisionBoxes(visibleBounds, pos->world.Bounds()))
        {
            visible = true;
            return true;
        }
        visible = false;
        return false;
    }
    virtual void SetVisibility(bool value)
    {
        if (value != visible) visible = value;
    }
    virtual bool GetVisibility()
    {
        return visible;
    }
    virtual Position* GetPos() {return nullptr;};
};

