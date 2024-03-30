#include "graphics/transition.h"

IrisTransition::IrisTransition(float TIME, Color COLOR, int WIDTH, int HEIGHT)
{
    time = TIME;
    color = COLOR;
    width = WIDTH;
    height = HEIGHT;
    targetX = WIDTH / 2;
    targetY = HEIGHT / 2;
    canvas = LoadRenderTexture(WIDTH, HEIGHT);
}

IrisTransition::~IrisTransition()
{
    UnloadRenderTexture(canvas);
}

bool IrisTransition::FadeIn()
{
    if(intimer < time)
    {
        intimer += GetFrameTime();
        float alpha = 1 - (intimer / time);
        float radius = (width / 2) * alpha;
        ClearBackground(color);
        DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, radius, BLANK);
        //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(color, alpha));
        return false;
    }
    return true;
}

bool IrisTransition::FadeOut()
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