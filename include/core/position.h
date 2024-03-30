#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cstddef>

class Position
{
public:
    //Vector3 translation = Vector3Zero();
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    Vector3 rotation = Vector3Zero();
    Vector3 scale = Vector3One();

    Position World();
    void Translate(float x, float y, float z = 0);
    void Translate(Vector3 vec);
    void Translate(Position *pos);

protected:
    Position* parent = NULL;
};