#include "core/position.h"
#include <raymath.h>

Vector2 Engine::Transform::Vec2()
{
    return Vector2{position.x, position.y};
}


void Engine::Transform::Translate(float X, float Y, float Z)
{
    position.x += X;
    position.y += Y;
    position.z += Z;
}

void Engine::Transform::Translate(Engine::Transform *pos)
{
    position = Vector3Add(position, pos->position);
}

void Engine::Transform::Translate(Vector3 vec)
{
    Translate(vec.x, vec.y, vec.z);
}

void Engine::Transform::Translate(Vector2 vec)
{
    Translate(vec.x, vec.y);
}