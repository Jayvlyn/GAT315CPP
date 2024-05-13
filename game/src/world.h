#pragma once
#include "raylib.h"
#include "body.h"

typedef struct jlBody jlBody;

extern jlBody* jlBodies;
extern int jlBodyCount;
extern Vector2 jlGravity;

jlBody* CreateBody(Vector2 position, float mass, jlBodyType bodyType);
void AddBody(jlBody* body);
void DestroyBody(jlBody* body);
void DestroyAllBodies();