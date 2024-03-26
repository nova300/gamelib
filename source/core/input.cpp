#include "core/input.h"
#include <raylib.h>

float getPitchInput()
{
    float i = 0.0f;
    if (IsKeyDown(KEY_DOWN)) i += 1;
    if (IsKeyDown(KEY_UP)) i += -1;
    return i;
}

float getTurnInput()
{
    float i = 0.0f;
    if (IsKeyDown(KEY_LEFT)) i += -1;
    if (IsKeyDown(KEY_RIGHT)) i += 1;
    return i;
}