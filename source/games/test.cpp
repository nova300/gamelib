#include "graphics/renderqueue.h"
#include "games/test.h"
#include "graphics/sprite.h"
#include "core/programstack.h"
#include "behaviours/playermovement.h"

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

void TestProgram::Init()
{
    auto sprite = player.AddBehaviour<Sprite>();
    sprite->Load(std::string("player.png"));

    player.AddBehaviour<PlayerMovement>();

    camera = {0};

    camera.zoom = 1;

    player.position.scale = Vector3{5.0f, 5.0f, 1.0f};

    AddObject(&player);
    rq.Add(&player);



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
    UpdateObjects(deltaTime);
}

void TestProgram::LateUpdate(float deltaTime)
{
    LateUpdateObjects(deltaTime);
}

void TestProgram::Destroy()
{
    RemoveObject(&player);
    rq.Remove(&player);
}

void TestProgram::Render()
{
    ClearBackground(BLUE);
    RenderQueue::RenderAll();
}