#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#include "render.h"

#define EDITOR_DATA(data) TextFormat("%0.2f", data), &data

bool ncEditorActive = true;
bool jlEditorIntersect = false;
Rectangle editorRect;
Texture2D cursorTexture;
jlEditorData_t jlEditorData;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");
    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    HideCursor();

    jlEditorData.anchor02 = (Vector2){ 1400, 144 };
    jlEditorData.EditorBoxActive = true;
    jlEditorData.BodyTypeDropdownActive = 0;
    jlEditorData.BodyTypeDropdownEditMode = false;
    jlEditorData.MassSliderValue = 3.0f;
    jlEditorData.DampingSliderValue = 0.0f;
    jlEditorData.GravityScaleSliderValue = 10.0f;
    jlEditorData.StiffnessSliderValue = 10.0f;
    jlEditorData.RestitutionSliderValue = 0.0f;
    jlEditorData.GravitationSliderValue = 0.0f;
    jlEditorData.GravitySliderValue = 0.0f;
    jlEditorData.TimestepSliderValue = 50.0f;
    jlEditorData.SimulateToggleActive = true;
    jlEditorData.ResetButtonPressed = false;

    editorRect = (Rectangle){ jlEditorData.anchor02.x + 0, jlEditorData.anchor02.y + -8, 432, 696 };
}

void UpdateEditor(Vector2 position)
{
    // toggle show / hide editor box with key press
    if (IsKeyPressed(KEY_TAB)) jlEditorData.EditorBoxActive = !jlEditorData.EditorBoxActive;

    // check if cursor position is intersecting the editor box 
    jlEditorIntersect = jlEditorData.EditorBoxActive && CheckCollisionPointRec(position, editorRect);
}


void DrawEditor(Vector2 position)
{
    if (jlEditorData.BodyTypeDropdownEditMode) GuiLock();

    if (jlEditorData.EditorBoxActive)
    {
        jlEditorData.EditorBoxActive = !GuiWindowBox(editorRect, "Editor");
        GuiGroupBox((Rectangle) { jlEditorData.anchor02.x + 24, jlEditorData.anchor02.y + 56, 392, 288 }, "Body");
        GuiGroupBox((Rectangle) { jlEditorData.anchor02.x + 24, jlEditorData.anchor02.y + 368, 392, 256 }, "World");
        GuiSliderBar((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 128, 232, 24 }, "Mass", EDITOR_DATA(jlEditorData.MassSliderValue), 1, 10);
        GuiSliderBar((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 160, 232, 24 }, "Damping", EDITOR_DATA(jlEditorData.DampingSliderValue),0, 10);
        GuiSliderBar((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 192, 232, 24 }, "Gravity Scale", EDITOR_DATA(jlEditorData.GravityScaleSliderValue), 0, 20);
        GuiSliderBar((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 224, 232, 24 }, "Stiffness(k)", EDITOR_DATA(jlEditorData.StiffnessSliderValue), 0, 40);
        GuiSliderBar((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 256, 232, 24 }, "Restitution", EDITOR_DATA(jlEditorData.RestitutionSliderValue), 0, 1);
        GuiSliderBar((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 440, 232, 24 }, "Gravitation", EDITOR_DATA(jlEditorData.GravitationSliderValue), 0, 10);
        GuiSlider((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 408, 232, 24 }, "Gravity", EDITOR_DATA(jlEditorData.GravitySliderValue), -10, 10);
        GuiSliderBar((Rectangle) { jlEditorData.anchor02.x + 120, jlEditorData.anchor02.y + 472, 232, 24 }, "Timestep", EDITOR_DATA(jlEditorData.TimestepSliderValue), 0, 100);
        GuiToggle((Rectangle) { jlEditorData.anchor02.x + 232, jlEditorData.anchor02.y + 632, 184, 32 }, "SIMULATE", & jlEditorData.SimulateToggleActive);
        if (GuiDropdownBox((Rectangle) { jlEditorData.anchor02.x + 72, jlEditorData.anchor02.y + 80, 304, 32 }, "STATIC;KINEMATIC;DYNAMIC", & jlEditorData.BodyTypeDropdownActive, jlEditorData.BodyTypeDropdownEditMode)) jlEditorData.BodyTypeDropdownEditMode = !jlEditorData.BodyTypeDropdownEditMode;
        jlEditorData.ResetButtonPressed = GuiButton((Rectangle) { jlEditorData.anchor02.x + 24, jlEditorData.anchor02.y + 632, 192, 32 }, "RESET");
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width * 0.5f, (int)position.y - cursorTexture.height * 0.5f, WHITE);
    GuiUnlock();
}

jlBody* GetBodyIntersect(jlBody* bodies, Vector2 position)
{
    for (jlBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(jlBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}
