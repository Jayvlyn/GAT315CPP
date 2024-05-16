#pragma once
#include "raylib.h"

typedef struct jlContact jlContact_t;
typedef struct jlBody jlBody;

void CreateContacts(jlBody* bodies, jlContact_t** contacts);
jlContact_t* GenerateContact(jlBody* body1, jlBody* body2);

void SeparateContacts(jlContact_t* contacts);
void ResolveContacts(jlContact_t* contacts);