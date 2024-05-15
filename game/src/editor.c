#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#include "render.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;

Texture2D cursorTexture;

// GUI VARS
//bool EditorBoxActive = true;
jlEditorData_t jlEditorData;
bool jlEditorIntersect = false;
Vector2 anchor01 = { 1600, 40 };

bool WorldGroupBoxActive = true;
bool BodyTypeDropdownEditMode = false;
int BodyTypeDropdownActive = 0;
float MassMinSliderValue = 0.0f;
float GravitationSliderValue = 0.0f;
float MassMaxSliderValue = 0.0f;
float DampingSliderValue = 0.0f;
float GravityScaleSliderValue = 0.0f;


void InitEditor()
{
    GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");
    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    HideCursor();

    jlEditorData.anchor01 = (Vector2){ 1500, 48 };

    jlEditorData.WorldGroupBoxActive = true;
    jlEditorData.BodyTypeDropdownEditMode = false;
    jlEditorData.BodyTypeDropdownActive = 0;
    jlEditorData.MassMinSliderValue = 0.0f;
    jlEditorData.GravitationSliderValue = 0.0f;
    jlEditorData.DampingSliderValue = 0.0f;
    jlEditorData.GravityScaleSliderValue = 0.0f;
    jlEditorData.GravitySliderValue = 0.0f;
    jlEditorData.StiffnessSliderValue = 0.0f;

    editorRect = (Rectangle){ jlEditorData.anchor01.x + 0, jlEditorData.anchor01.y + 0, 300, 600 };

}

void UpdateEditor(Vector2 position)
{
    // toggle show / hide editor box with key press
    if (IsKeyPressed(KEY_TAB)) jlEditorData.WorldGroupBoxActive = !jlEditorData.WorldGroupBoxActive;

    // check if cursor position is intersecting the editor box 
    ncEditorIntersect = jlEditorData.WorldGroupBoxActive && CheckCollisionPointRec(position, editorRect);
}


void DrawEditor(Vector2 position)
{
    if (jlEditorData.BodyTypeDropdownEditMode) GuiLock();

    if (jlEditorData.WorldGroupBoxActive)
    {
        jlEditorData.WorldGroupBoxActive = !GuiWindowBox((Rectangle) { jlEditorData.anchor01.x + 16, jlEditorData.anchor01.y + 280, 272, 256 }, "World");
        GuiGroupBox((Rectangle) { jlEditorData.anchor01.x + 0, jlEditorData.anchor01.y + 0, 304, 624 }, "Editor");
        GuiGroupBox((Rectangle) { jlEditorData.anchor01.x + 16, jlEditorData.anchor01.y + 40, 272, 224 }, "Body");
        GuiSliderBar((Rectangle) { jlEditorData.anchor01.x + 104, jlEditorData.anchor01.y + 96, 168, 24 }, "Mass", NULL, & jlEditorData.MassMinSliderValue, 0, 100);
        GuiSliderBar((Rectangle) { jlEditorData.anchor01.x + 104, jlEditorData.anchor01.y + 360, 168, 24 }, "Gravitation", NULL, & jlEditorData.GravitationSliderValue, 0, 100);
        GuiSliderBar((Rectangle) { jlEditorData.anchor01.x + 104, jlEditorData.anchor01.y + 136, 168, 24 }, "Damping", NULL, & jlEditorData.DampingSliderValue, 0, 100);
        GuiSliderBar((Rectangle) { jlEditorData.anchor01.x + 104, jlEditorData.anchor01.y + 176, 168, 24 }, "Gravity Scale", NULL, & jlEditorData.GravityScaleSliderValue, 0, 100);
        GuiSliderBar((Rectangle) { jlEditorData.anchor01.x + 104, jlEditorData.anchor01.y + 320, 168, 24 }, "Gravity", NULL, & jlEditorData.GravitySliderValue, 0, 100);
        GuiSliderBar((Rectangle) { jlEditorData.anchor01.x + 104, jlEditorData.anchor01.y + 216, 168, 24 }, "Stiffness(k)", NULL, & jlEditorData.StiffnessSliderValue, 0, 100);
        if (GuiDropdownBox((Rectangle) { jlEditorData.anchor01.x + 32, jlEditorData.anchor01.y + 64, 240, 24 }, "STATIC;KINEMATIC;DYNAMIC", & jlEditorData.BodyTypeDropdownActive, jlEditorData.BodyTypeDropdownEditMode)) jlEditorData.BodyTypeDropdownEditMode = !jlEditorData.BodyTypeDropdownEditMode;
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
