#include "graphics/renderqueue.h"
#include "games/test.h"
#include "graphics/sprite.h"
#include "core/programstack.h"
#include "behaviours/playermovement.h"
#include "graphics/animatedsprite.h"
#include "graphics/textureatlas.h"


#include <raylib.h>

int main(void)
{

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "LibGame V.2");
    SetTargetFPS(60);

    ProgramStack ps1;
    ps1.Switch(new TestProgram());


    while(!WindowShouldClose())
    {
        ps1.Update(GetFrameTime());

        BeginDrawing();
            ps1.Render();
        EndDrawing();
    }

    CloseWindow();

}


void UpdateCameraPlayerBoundsPush(Camera2D *camera, Object *player, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = (Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
    if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
    if (player->position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
    if (player->position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
}

void TestProgram::Init()
{
    canvas = LoadRenderTexture(canvaswidth, canvasheight);
    TextureAtlas atlas = TextureAtlas(std::string("player.png"), 32, 32);

    auto sprite = player.AddBehaviour<AnimatedSprite>();
    
    sprite->PushFrame(PlayerAnimations::DOWN, atlas.GetSpriteFrame(1));

    sprite->PushFrame(PlayerAnimations::UP, atlas.GetSpriteFrame(6));

    sprite->PushFrame(PlayerAnimations::SIDE, atlas.GetSpriteFrame(2));

    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(1));
    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(0));
    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(1));
    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(8));

    sprite->PushFrame(PlayerAnimations::RUN_SIDE, atlas.GetSpriteFrame(2, 0.0f));
    sprite->PushFrame(PlayerAnimations::RUN_SIDE, atlas.GetSpriteFrame(3, 0.05f));
    sprite->PushFrame(PlayerAnimations::RUN_SIDE, atlas.GetSpriteFrame(2, 0.05f));

    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(6));
    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(7));
    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(6));
    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(9));


    player.AddBehaviour<PlayerMovement>();

    camera = {0};

    camera.zoom = 1;

    //player.position.scale = Vector3{1f, 5.0f, 1.0f};

    AddObject(&player);
    rq.AddRender(&player);



    ProcessNewObjects();
}

bool TestProgram::FadeIn()
{
    return trans.FadeIn();
}

bool TestProgram::FadeOut()
{
    return trans.FadeOut();
}

void TestProgram::Update(float deltaTime)
{
    UpdateCameraPlayerBoundsPush(&camera, &player, canvaswidth, canvasheight);
    UpdateObjects(deltaTime);
}

void TestProgram::PostUpdate(float deltaTime)
{
    PostUpdateObjects(deltaTime);

    //BeginTextureMode(canvas);
    //    ClearBackground(BLACK);
    //    rq.DrawRender();
    //EndTextureMode();
}

void TestProgram::Destroy()
{
    RemoveObject(&player);
    rq.RemoveRender(&player);

    UnloadRenderTexture(canvas);
}

void TestProgram::Render()
{
    ClearBackground(BLUE);

    rq.DrawRender();

    /*const float virtualRatio =  (float)canvaswidth / (float)canvasheight;
    float screenHeight = GetScreenHeight();
    if(screenHeight < 1.0f) screenHeight = 1.0f;
    const float screenRatio = (float)GetScreenWidth() / screenHeight;

    const float desiredWidth = (float)(GetScreenWidth() -  2 * marginX);
    const float desiredHeight = (float)(GetScreenHeight() - 2 * marginY);

    float adjustedX = marginX;
    float adjustedY = marginY;
    float adjustedWidth = desiredWidth;
    float adjustedHeight = desiredHeight;

    if(virtualRatio > screenRatio)
    {
        adjustedHeight = desiredWidth / virtualRatio;
        float centering = (GetScreenHeight() - adjustedHeight) / 2;
        adjustedY = centering;
        //printf("adjusting height\n");
    }
    else if(virtualRatio < screenRatio)
    {
        adjustedWidth = desiredHeight * virtualRatio;
        float centering = (GetScreenWidth() - adjustedWidth) / 2;
        adjustedX = centering;
        //printf("adjusting width\n");
    }
    DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)canvaswidth, (float)-canvasheight}, Rectangle{adjustedX, adjustedY, adjustedWidth, adjustedHeight} , Vector2Zero(), 0.0f, WHITE);
    */

}