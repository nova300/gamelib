#include "graphics/renderqueue.h"
#include "games/test.h"
#include "graphics/sprite.h"
#include "core/programstack.h"
#include "behaviours/playermovement.h"

int main(void)
{

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "LibGame V.2");

    SetTargetFPS(60);
    ProgramStack ps1;

    ps1.Push(new TestProgram());


    while(!WindowShouldClose())
    {
        ps1.Update(GetFrameTime());

        BeginDrawing();
            ClearBackground(BLUE);
            RenderQueue::RenderAll();
        EndDrawing();
    }

    CloseWindow();

}

void TestProgram::Init()
{
    player = std::make_shared<Object>();

    auto sprite = player->AddBehaviour<Sprite>();
    sprite->Load(std::string("player.png"));

    player->AddBehaviour<PlayerMovement>();

    GetQueue()->Add(player);
    os1.Add(player);


}

void TestProgram::Update(float deltaTime)
{
    os1.Update(deltaTime);
}

void TestProgram::LateUpdate(float deltaTime)
{
    os1.LateUpdate(deltaTime);
}

void TestProgram::Destroy()
{
    
}

void TestProgram::Render()
{

}