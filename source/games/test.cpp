#include "graphics/renderqueue.h"
#include "games/test.h"
#include "graphics/sprite.h"
#include "core/programstack.h"
#include "graphics/lights.h"

int main(void)
{

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "LibGame V.2");

    SetTargetFPS(60);
    ProgramStack ps1;

    Lights lights(Rectangle{30.0, 20.0, 300.0, 200.0});


    auto light1 = lights.SetupLight(300.0f, WHITE);

    light1->Set(Vector2{50.0, 50.0});

    auto occ1 = lights.SetupOccluder();

    occ1->Set(Rectangle{100.0, 100.0, 30.0, 30.0});

    //ps1.Push(new TestProgram());


    while(!WindowShouldClose())
    {
        //ps1.Update(GetFrameTime());
        lights.Update(GetFrameTime());

        BeginDrawing();
            lights.Render();
            //ps1.Render();
        EndDrawing();
    }

    CloseWindow();

}

void TestProgram::Init()
{
    player = std::make_shared<Object>();

    auto sprite = player->AddBehaviour<Sprite>();
    sprite->Load(std::string("player.png"));

    rq1.Add(player);
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
    rq1.Draw();
}