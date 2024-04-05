#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cstddef>
class Object;

struct CollisionInfo
{
    Object *other = NULL;
    Vector2 position = Vector2Zero();
    Vector2 pushout = Vector2Zero();
    Vector2 normal = Vector2Zero();
};

enum CollisionShape
{
    COL_UNDEFINED,
    COL_POINT,
    COL_BOX,
    COL_SPRITE,
    COL_CIRCLE
};