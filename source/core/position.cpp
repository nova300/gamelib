#include "core/position.h"
#include <raymath.h>

Position Position::World()
{ 
    if(this->parent)
    {
        Position outp = this->parent->World();
        outp.translation = Vector3Add(outp.translation, this->translation);
        outp.rotation = Vector3Add(outp.rotation, this->rotation);
        outp.scale = Vector3Add(outp.scale, this->scale);
        return outp;
    }

    Position out = *this;

    return out;
}