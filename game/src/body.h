#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum
{
	STATIC,
	KINEMATIC,
	DYNAMIC
} jlBodyType;

typedef struct jlBody
{
	jlBodyType body;
	// force -> acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 force;

	float mass;
	float inverseMass; // 1 / mass (static = 0)

	struct jlBody* next;
	struct jlBody* prev;
} jlBody;

inline void ApplyForce(jlBody* body, Vector2 force)
{
	body->force = Vector2Add(body->force, force);
}

inline void ClearForce(jlBody* body)
{
	body->force = Vector2Zero();
}
