#include "graphics/transition.h"

FadeTransition::FadeTransition(float TIME, Color COLOR)
{
    time = TIME;
    color = COLOR;
}

FadeTransition::~FadeTransition()
{

}

bool FadeTransition::FadeIn()
{
    if(intimer < time)
    {
        intimer += GetFrameTime();
        float alpha = 1 - (intimer / time);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(color, alpha));
        return false;
    }
    return true;
}

bool FadeTransition::FadeOut()
{
    if(outtimer < time)
    {
        intimer += GetFrameTime();
        float alpha = intimer / time;
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(color, alpha));
        return false;
    }
    return true;
}