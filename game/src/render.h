#pragma once
#include "raylib.h"
#include "raymath.h"

extern Vector2 jlScreenSize;
extern float jlScreenZoom;
extern float jlViewSize;

Vector2 ConvertScreenToWorld(Vector2 screen);
Vector2 ConvertWorldToScreen(Vector2 world);
float ConvertWorldToPixel(float world);
