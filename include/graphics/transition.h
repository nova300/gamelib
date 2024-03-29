#pragma once

#include <raylib.h>

class FadeTransition
{
public:
    FadeTransition(float time = 1.0f, Color color = BLACK);
    ~FadeTransition();
    bool FadeIn();
    bool FadeOut();
private:
    Color color;
    float time = 1.0f;
    float intimer = 0.0f;
    float outtimer = 0.0f;
};