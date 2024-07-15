#include "graphics/transition.h"
#include <raymath.h>
#include "utils/utils.h"


IrisTransition::IrisTransition(float TIME, Color COLOR, int WIDTH, int HEIGHT, Vector2 target)
{
    time = TIME;
    color = COLOR;
    width = WIDTH;
    height = HEIGHT;
    targetX = target.x;
    targetY = target.y;
    canvas = LoadRenderTexture(WIDTH, HEIGHT);
}

IrisTransition::~IrisTransition()
{
    UnloadRenderTexture(canvas);
}

void IrisTransition::Update(int x, int y)
{
    if(x == -1) x = targetX;
    if(y == -1) y = targetY;
    BeginTextureMode(canvas);
        
        ClearBackground(color);
        //DrawRectangle(0.0f, 0.0f, width, height, BLACK);
        BeginBlendMode(BLEND_SUBTRACT_COLORS);
        DrawCircle(x, y, currentRadius, color);

        EndBlendMode();

    EndTextureMode();
}

bool IrisTransition::FadeIn()
{
    if(intimer < time)
    {
        intimer += GetFrameTime();
        float alpha = intimer / time;
        currentRadius = (width / 2) * alpha;
        currentRadius += currentRadius / 4;
        DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)width, (float)-height}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, 50, 50), Vector2Zero(), 0.0f, WHITE);
        return false;
    }
    intimer = 0.0f;
    return true;
}

bool IrisTransition::FadeOut()
{
    if(outtimer < time)
    {
        outtimer += GetFrameTime();
        float alpha = 1 - (outtimer / time);
        currentRadius = (width / 2) * alpha;
        currentRadius += currentRadius / 4;
        DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)width, (float)-height}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)width, (float)height}, 50, 50) , Vector2Zero(), 0.0f, WHITE);
        return false;
    }
    outtimer = 0.0f;
    return true;
}