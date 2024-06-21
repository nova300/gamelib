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
    virtual Position* GetPos() {return nullptr;};
};

