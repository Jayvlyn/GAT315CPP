#pragma once
#include "body.h"

extern jlBody* jlBodies;
extern int jlBodyCount;

jlBody* CreateBody();
void DestroyBody(jlBody* body);
void DestroyAllBodies();