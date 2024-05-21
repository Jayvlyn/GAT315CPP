#pragma once
#include "raylib.h"
#include "body.h"

//typedef struct jlEditorData
//{
//	float SliderMinValue;
//	float SliderMaxValue;
//	float SliderGravitationValue;
//} jlEditorData_t;

typedef struct jlEditorData
{
    Vector2 anchor02;

    bool EditorBoxActive;
    bool BodyTypeDropdownEditMode;
    int BodyTypeDropdownActive;
    float MassSliderValue;
    float DampingSliderValue;
    float GravityScaleSliderValue;
    float StiffnessSliderValue;
    float RestitutionSliderValue;
    float GravitationSliderValue;
    float GravitySliderValue;
    float TimestepSliderValue;
    bool SimulateToggleActive;
    bool ResetButtonPressed;

} jlEditorData_t;

extern jlEditorData_t jlEditorData;
extern bool jlEditorIntersect;

extern bool ncEditorActive;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct jlBody* GetBodyIntersect(struct jlBody* bodies, Vector2 position); 
void DrawLineBodyToPosition(struct jlBody* body, Vector2 position);