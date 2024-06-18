/*******************************************************************************************
*
*   MAPEDIT v1.0.0 - Map Editor
*
*   MODULE USAGE:
*       #define GUI_MAPEDIT_IMPLEMENTATION
*       #include "gui_MAPEDIT.h"
*
*       INIT: GuiMAPEDITState state = InitGuiMAPEDIT();
*       DRAW: GuiMAPEDIT(&state);
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

#ifndef GUI_MAPEDIT_H
#define GUI_MAPEDIT_H

typedef struct {
    bool WindowBox000Active;
    bool Spinner001EditMode;
    int Spinner001Value;
    bool paintButtonPressed;
    bool replaceButtonPressed;
    bool replaceDialogOpen;
    bool replaceCancelPressed;

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiMAPEDITState;

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
GuiMAPEDITState InitGuiMAPEDIT(void);
void GuiMAPEDIT(GuiMAPEDITState *state);


#ifdef __cplusplus
}
#endif

#endif // GUI_MAPEDIT_H

/***********************************************************************************
*
*   GUI_MAPEDIT IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_MAPEDIT_IMPLEMENTATION)

#include "raygui.h"
#include "editor.h"

GuiMAPEDITState InitGuiMAPEDIT(void)
{
    GuiMAPEDITState state = { 0 };

    state.WindowBox000Active = false;
    state.Spinner001EditMode = false;
    state.Spinner001Value = 0;
    state.paintButtonPressed = false;
    state.replaceButtonPressed = false;
    state.replaceDialogOpen = false;
    state.replaceCancelPressed = false;

    // Custom variables initialization

    return state;
}


void GuiMAPEDIT(GuiMAPEDITState *state)
{
    if(state->replaceDialogOpen)
    {
        state->replaceDialogOpen = !GuiWindowBox(Rectangle{ 48, 48, 216, 216 }, "REPLACE TILE");
        GuiLabel(Rectangle{ 86, 100, 120, 24 }, "DRAG AND DROP IMAGE TO REPLACE");
        return;
    }
    state->WindowBox000Active = GuiWindowBox(Rectangle{ 24, 24, 216, 302 }, "MAP EDIT");
    if (GuiSpinner(Rectangle{ 72, 216, 120, 24 }, "Texture", &state->Spinner001Value, 0, 1000, state->Spinner001EditMode)) state->Spinner001EditMode = !state->Spinner001EditMode;
    state->paintButtonPressed = GuiButton(Rectangle{ 72, 248, 120, 24 }, "PAINT");
    state->replaceButtonPressed = GuiButton(Rectangle{ 72, 272, 120, 24 }, "REPLACE");
}

#endif // GUI_MAPEDIT_IMPLEMENTATION
