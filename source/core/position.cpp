#include "core/position.h"
#include <raymath.h>

Position Position::World()
{ 
    if(this->parent)
    {
        Position outp = this->parent->World();
        outp.Translate(this);
        outp.rotation = Vector3Add(outp.rotation, this->rotation);
        outp.scale = Vector3Add(outp.scale, this->scale);
        return outp;
    }

    Position out = *this;

    return out;
}

Vector2 Position::Vec2()
{
    return Vector2{x, y};
}


void Position::Translate(float X, float Y, float Z)
{
    x += X;
    y += Y;
    z += Z;
}

void Position::Translate(Position *pos)
{
    x += pos->x;
    y += pos->y;
    z += pos->z;
}

void Position::Translate(Vector3 vec)
{
    Translate(vec.x, vec.y, vec.z);
}