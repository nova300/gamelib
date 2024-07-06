#include "graphics/renderqueue.h"
#include "demos/test.h"
#include "graphics/sprite.h"
#include "core/programstack.h"
#include "behaviours/playermovement.h"
#include "graphics/animatedsprite.h"
#include "graphics/textureatlas.h"
#include "utils.h"
#include "objects/commandproc.h"
#include "objects/debugconsole.h"
#include "graphics/texturecache.h"

#include <raylib.h>
#include <raymath.h>
#include <raygui.h>

#include "player.png.inc.c"

int main(void)
{
    DebugConsole::RegisterPrograms();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1024, 738, "LibGame V.2");
    SetTargetFPS(60);

    SetPackedTexturePtr(PLAYER_PNG_DATA, PLAYER_PNG_DATA_SIZE, PLAYER_PNG_DATA_PATH);

    ProgramStack ps1;
    ps1.Switch(new TestProgram);

    GuiLoadStyleDefault();
    GuiLoadStyle("candy_ts.rgs");


    while(!WindowShouldClose() && !ps1.Stop())
    {
        ps1.Update(GetFrameTime());

        BeginDrawing();
            ps1.Render();
        EndDrawing();
    }

    ps1.Clear();

    CloseWindow();

}

static void UpdateCameraPlayerBoundsPush(Camera2D *camera, Object *player, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D(Vector2{ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D(Vector2{ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = Vector2{ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->position.local.position.x < bboxWorldMin.x) camera->target.x = player->position.local.position.x;
    if (player->position.local.position.y < bboxWorldMin.y) camera->target.y = player->position.local.position.y;
    if (player->position.local.position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.local.position.x - bboxWorldMax.x);
    if (player->position.local.position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.local.position.y - bboxWorldMax.y);
}

void TestProgram::Init()
{
    canvas = LoadRenderTexture(canvaswidth, canvasheight);
    TextureAtlas atlas = TextureAtlas(std::string("player.png"), 32, 32);

    player = root.AddChild().lock();
    map = root.AddChild().lock();

    auto sprite = player->AddBehaviour<AnimatedSprite>().lock();
    
    sprite->PushFrame(PlayerAnimations::DOWN, atlas.GetSpriteFrame(1));

    sprite->PushFrame(PlayerAnimations::UP, atlas.GetSpriteFrame(6));

    sprite->PushFrame(PlayerAnimations::SIDE, atlas.GetSpriteFrame(2));

    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(1));
    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(0));
    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(1));
    sprite->PushFrame(PlayerAnimations::RUN_DOWN, atlas.GetSpriteFrame(8));

    sprite->PushFrame(PlayerAnimations::RUN_SIDE, atlas.GetSpriteFrame(2, 0.05f));
    sprite->PushFrame(PlayerAnimations::RUN_SIDE, atlas.GetSpriteFrame(3, 0.05f));
    sprite->PushFrame(PlayerAnimations::RUN_SIDE, atlas.GetSpriteFrame(2, 0.05f));

    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(6));
    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(7));
    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(6));
    sprite->PushFrame(PlayerAnimations::RUN_UP, atlas.GetSpriteFrame(9));


    player->AddBehaviour<PlayerMovement>();

    camera = {0};

    camera.zoom = 1;

    player->position.local.position.z = 1.0f;



    auto mapsprite = map->AddBehaviour<Sprite>().lock();

    auto mapimg = GenImageChecked(2000, 2000, 16, 16, GREEN, DARKGREEN);

    auto maptex = CLoadTexture(mapimg);
    
    mapsprite->Load(maptex);

    UnloadImage(mapimg);


    window1 = root.AddChild().lock();

    window1->position.local.size = Vector3{100, 200, 0};
    window1->position.local.position = Vector3{50, 50, 0};

    auto win = window1->AddBehaviour<Window>().lock();


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
    wm.MouseInput(GetMousePosition());
    UpdateCameraPlayerBoundsPush(&camera, player.get(), canvaswidth, canvasheight);

    if(IsKeyPressed(KEY_F1))
    {
        GetStack()->Push(new Terminal(new DebugConsole()));
    }
    if(IsKeyPressed(KEY_F2))
    {
        std::string alpha;
        for(unsigned char c = 0; c < 255; c++)
        {
            alpha.push_back(c);
        }
        alpha.push_back((char)255);
        GetStack()->Push(new Terminal(new CmdMessage(alpha)));
    }
    if(IsKeyPressed(KEY_F3))
    {
        
    }
    auto objs = root.GetAllOfType<GeoObject>(true);
        int i = 0;
        for(auto o : objs)
        {
            auto world = o->GetPos()->world;
            printf("OBJECT: %d, POS: %f, %f\n", i, world.position.x, world.position.y);
            i++;
        }
}

void TestProgram::SoftRender()
{
    auto vec1 = GetWorldToScreen2D(Vector2{player->position.world.position.x + 16, player->position.local.position.y + 16}, camera);
    vec1.x /= 2;
    vec1.y /= 2;
    trans.Update((int)vec1.x, (int)vec1.y);

    auto c = ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)canvaswidth, (float)canvasheight}, 50, 50);

    Vector2 mouse = GetMousePosition();
    //mouse.x -= marginX;
    //mouse.y -= marginY;

    mouse.x -= c.x;
    mouse.y -= c.y;

    mouse.x /= c.width;
    mouse.y /= c.height;
    mouse.x *= canvaswidth;
    mouse.y *= canvasheight;

    //Vector2 mousepos = {0};

    

    //Vector2 mousepos = GetScreenToWorld2D(mouse, camera);
    
    

    //printf("X: %f Y: %f\n", mouse.x, mouse.y);

    BeginTextureMode(canvas);
        ClearBackground(DARKGRAY);
        rq.DrawRender();
        //rawCircle(mouse.x, mouse.y, 32.0f, RED);
    EndTextureMode();
}   

void TestProgram::PostUpdate(float deltaTime)
{

}

void TestProgram::Destroy()
{

    UnloadRenderTexture(canvas);
}

RenderQueue* TestProgram::GetRenderQueue(int index)
{
    switch (index)
    {
    case RQ_WINDOWS:
        return &wm;
    
    default:
        return &rq;
    }
    
}

void TestProgram::Render()
{
    ClearBackground(DARKBLUE);

    //rq.DrawRender();
    DrawTexturePro(canvas.texture, Rectangle{0.0f, 0.0f, (float)canvaswidth, (float)-canvasheight}, ScaleCanvasKeepAspect(Rectangle{0.0f, 0.0f, (float)canvaswidth, (float)canvasheight}, 50, 50) , Vector2Zero(), 0.0f, WHITE);
    wm.DrawRender();
}