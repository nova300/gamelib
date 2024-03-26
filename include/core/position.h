#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cstddef>

class Position
{
public:
    Vector3 translation = Vector3Zero();
    Vector3 rotation = Vector3Zero();
    Vector3 scale = Vector3One();

    Position World();

protected:
    Position* parent = NULL;
};