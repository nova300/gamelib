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
    virtual Position* GetPos() {return nullptr;};
};

