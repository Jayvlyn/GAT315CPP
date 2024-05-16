#pragma once
#include "raylib.h"

typedef struct jlContact
{
	struct jlBody* body1;
	struct jlBody* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct jlContact* next;
} jlContact_t;

void AddContact(jlContact_t* contact, jlContact_t** contacts);
void DestroyAllContacts(jlContact_t** contacts);
