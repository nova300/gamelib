#pragma once
#include <raylib.h>
#include "tools/tilemapedit/gui/gui_editor.h"
#include "tools/tilemapedit/gui/gui_MAPEDIT.h"

enum EditorState
{
    NONE,
    MAP
};

class Selector : public Object
{
    public:
    void Update(void);
    void Render(void);
    void Render2D(void);
    void SearchTarget(TileSet *ts);
    bool Sample();
    Vector2 pos;
    bool active = false;
    bool spill = false;
    int texture = 0;
    bool target = false;
    TileSet::Tile *targetTile = NULL;
};

class EditorScreen : public Program
{
public:
    ~EditorScreen() {};
    void Update(float deltaTime) override;
    void Render() override;
    void Init() override;
    void Destroy() override;
private:
    GuiMAPEDITState mestate;
    GuiEditorState estate;
    EditorState editorState = NONE;
    Camera2D camera;
    Object player;
    Object tilemap;
    RenderQueueSorted2D rq = RenderQueueSorted2D(&camera);
    ObjectStore os;
};