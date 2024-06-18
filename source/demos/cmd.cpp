#include "graphics/renderqueue.h"
#include "games/cmd.h"
#include "objects/console.h"
#include "graphics/sprite.h"
#include "core/programstack.h"
#include "behaviours/playermovement.h"
#include "graphics/animatedsprite.h"
#include "graphics/textureatlas.h"
#include "utils.h"
#include "objects/commandproc.h"


#include <raylib.h>
#include <raymath.h>

/*int main(void)
{
    CommandProcessor::RegisterPrograms();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1024, 738, "COMMAND");
    SetTargetFPS(60);

    ProgramStack ps1;
    ps1.Switch(new CmdProgram());


    while(!WindowShouldClose())
    {
        ps1.Update(GetFrameTime());

        BeginDrawing();
            ps1.Render();
        EndDrawing();
    }

    ps1.Clear();

    CloseWindow();

}*/

void CmdProgram::Init()
{
    console.Init();
}

void CmdProgram::Update(float deltaTime)
{

    auto& stream = console.GetStream();

    cmd.Update(stream, this);

    if(IsKeyPressed(KEY_F2))
    {
        GetStack()->Switch(new CmdProgram());
    }
}

void CmdProgram::SoftRender()
{
    console.Render(WHITE, BLANK);
}

void CmdProgram::Render()
{
    ClearBackground(DARKBLUE);
    console.Draw(50, 50);
}