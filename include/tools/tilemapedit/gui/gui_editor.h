/*******************************************************************************************
*
*   Editor v1.0.0 - world editor
*
*   MODULE USAGE:
*       #define GUI_EDITOR_IMPLEMENTATION
*       #include "gui_editor.h"
*
*       INIT: GuiEditorState state = InitGuiEditor();
*       DRAW: GuiEditor(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 Max Fagerstrom. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

typedef struct {
    bool Button001Pressed;
    bool Button002Pressed;
    bool Button004Pressed;

    bool WindowBox000Active;
    bool Button003Pressed;
    bool Button005Pressed;
    bool TextBox002EditMode;
    char TextBox002Text[128];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiEditorState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiEditorState InitGuiEditor(void);
void GuiEditor(GuiEditorState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_EDITOR_H

/***********************************************************************************
*
*   GUI_EDITOR IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_EDITOR_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiEditorState InitGuiEditor(void)
{
    GuiEditorState state = { 0 };

    state.Button001Pressed = false;
    state.Button002Pressed = false;
    state.Button004Pressed = false;

    state.WindowBox000Active = false;
    state.Button003Pressed = false;
    state.Button005Pressed = false;
    state.TextBox002EditMode = false;
    strcpy(state.TextBox002Text, "level.dat");

    // Custom variables initialization

    return state;
}

void GuiEditor(GuiEditorState *state)
{
    GuiGroupBox(Rectangle{ 24, 24, 152, 132 }, "World Edit");
    
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(Rectangle{ 48, 48, 240, 120 }, "FILE");
        state->Button003Pressed = GuiButton(Rectangle{ 96, 136, 56, 24 }, "Save");
        state->Button005Pressed = GuiButton(Rectangle{ 184, 136, 56, 24 }, "Load");  
        if (GuiTextBox(Rectangle{ 72, 96, 192, 24 }, state->TextBox002Text, 128, state->TextBox002EditMode)) state->TextBox002EditMode = !state->TextBox002EditMode;
    }
    else
    {
        state->Button004Pressed = GuiButton(Rectangle{ 40, 56, 120, 24 }, "FILE");
        state->Button001Pressed = GuiButton(Rectangle{ 40, 88, 120, 24 }, "MAP"); 
        state->Button002Pressed = GuiButton(Rectangle{ 40, 120, 120, 24 }, "OBJECTS"); 
    }
}

#endif // GUI_EDITOR_IMPLEMENTATION
