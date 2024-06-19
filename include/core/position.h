#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cstddef>

namespace Engine
{
    struct Transform
    {
        Vector3 position = Vector3Zero();
        Vector3 rotation = Vector3Zero();
        Vector3 scale = Vector3One();

        Vector2 Vec2();
        void Translate(float x, float y, float z = 0);
        void Translate(Vector3 vec);
        void Translate(Transform *pos);
        void Translate(Vector2 vec);
    };
};

class Position
{
public:
    Engine::Transform local;
    Engine::Transform world;
};