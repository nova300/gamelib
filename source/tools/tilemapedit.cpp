#include "tools/tilemapedit/editor.h"
#include <raylib.h>

void DisplayText(const char* text)
{
    int halfText = MeasureText(text, 20) / 2;
    DrawText(text, (GetScreenWidth() / 2) - halfText, GetScreenHeight() / 2, 20, WHITE);
}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(640, 480, "MAP EDITOR");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(BLUE);
            DisplayText("MAP EDITOR V.2");
        EndDrawing();
    }

    CloseWindow();

}

#include <iostream>

#define GUI_EDITOR_IMPLEMENTATION
#include "tools/tilemapedit/gui/gui_editor.h"

#define GUI_MAPEDIT_IMPLEMENTATION
#include "tools/tilemapedit/gui/gui_MAPEDIT.h"

bool blink = false;
TileSet *tileSet0 = NULL;

static Rectangle targetBounds;

void EditorScreen::Update(float deltaTime)
{
    camera.offset.x = GetScreenHeight() / 2;
    camera.offset.y = GetScreenHeight() / 2;
    selector.pos = GetScreenToWorld2D(GetMousePosition(), camera);
    selector.SearchTarget(&ts);
    if(IsKeyDown(KEY_A)) camera.target.x -= 500.0f * deltaTime;
    if(IsKeyDown(KEY_D)) camera.target.x += 500.0f * deltaTime;
    if(IsKeyDown(KEY_W)) camera.target.y -= 500.0f * deltaTime;
    if(IsKeyDown(KEY_S)) camera.target.y += 500.0f * deltaTime;
    camera.zoom += GetMouseWheelMove() * deltaTime;

    switch (editorState)
    {
    case NONE:
        if (estate.Button001Pressed) editorState = MAP;
        if (estate.Button002Pressed) editorState = NONE;
        if (estate.Button004Pressed) 
        {
            estate.Button004Pressed = false;
            estate.WindowBox000Active = true;
        }
        if (estate.Button003Pressed)
        {
            estate.Button003Pressed = false;
            ts.SaveTiles(estate.TextBox002Text);
        }
        if (estate.Button005Pressed)
        {
            estate.Button005Pressed = false;
            ts.LoadTiles(estate.TextBox002Text);
        }
        break;

    case MAP:
        if (mestate.WindowBox000Active) 
        {
            editorState = NONE;
            selector.active = false;
        }
        if(selector.Sample())
        {
            mestate.Spinner001Value = selector.texture;
        }
        else selector.texture = mestate.Spinner001Value;
        if (mestate.paintButtonPressed) selector.active = true;
        if (mestate.replaceButtonPressed)
        {
            mestate.replaceButtonPressed = false;
            mestate.replaceDialogOpen = true;
        }
        if (mestate.replaceDialogOpen)
        {
            if(IsFileDropped())
            {
                FilePathList list = LoadDroppedFiles();
                ts.atlas.LoadCell(list.paths[0], mestate.Spinner001Value);
                UnloadDroppedFiles(list);
                mestate.replaceDialogOpen = false;
            }
        }
        break;

    default:
        break;
    }
}
void EditorScreen::Render()
{
    BeginMode2D(camera);
    RenderSprites(manager);
    EndMode2D();

    mapQueue.Render();

    DrawTextf(TextFormat("X: %f Y: %f", camera.target.x, camera.target.y), 500, 20, 10, RED );

    switch (editorState)
    {
    case NONE:
        GuiEditor(&estate);
        break;

    case MAP:
        GuiMAPEDIT(&mestate);
        ts.atlas.Draw(Rectangle{ 72, 72, 120, 120}, mestate.Spinner001Value);
        
        if(selector.active) DrawRectangleLinesEx(Rectangle{ 67, 67, 125, 125}, 5.0f, RED);
        else DrawRectangleLinesEx(Rectangle{ 67, 67, 125, 125}, 5.0f, LIGHTGRAY);

        break;

    default:
        break;
    }
}

void EditorScreen::Init()
{
    ts.LoadTiles(100, 100);
    tileSet0 = &ts;

    AddObject(&ts);
    AddObject(&selector);

    mapQueue.SetCam(&camera);
    mapQueue.Add(&ts);
    mapQueue.Add(&selector);

    camera.target.x = 0;
    camera.target.y = 0;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    estate = InitGuiEditor();

}
void EditorScreen::Destroy()
{

}

void Selector::Update()
{
    if (active)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            active = false;
        }
        if (target)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                targetTile->texture = this->texture;
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
            {
                targetTile->spill = !targetTile->spill;
            }
        }
    }
}

bool Selector::Sample()
{
    if (target && !active)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            this->texture = targetTile->texture;
            return true;
        }
    }
    return false;
}

void Selector::Render2D()
{
    if (target && active)
    {
        target = false;
        if(blink && tileSet0 != NULL) tileSet0->atlas.Draw(targetBounds, texture);
        DrawRectangleLinesEx(targetBounds, 5.0f, RED);
    }
}

void Selector::Render()
{

}

void Selector::SearchTarget(TileSet *ts)
{
    TileSet::Tile *t = ts->GetTileAtPos(pos, &targetBounds);
    if (t != NULL)
    {
        target = true;
        targetTile = t;
    }
    else
    {
        target = false;
        targetTile = NULL;
    }
}