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
    Vector2 anchor01;

    bool WorldGroupBoxActive;
    bool BodyTypeDropdownEditMode;
    int BodyTypeDropdownActive;
    float MassMinSliderValue;
    float GravitationSliderValue;
    float MassMaxSliderValue;
    float DampingSliderValue;
    float GravityScaleSliderValue;
} jlEditorData_t;

extern jlEditorData_t jlEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct jlBody* GetBodyIntersect(struct jlBody* bodies, Vector2 position); 
void DrawLineBodyToPosition(struct jlBody* body, Vector2 position);