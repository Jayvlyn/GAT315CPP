#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum
{
	BT_STATIC,
	BT_KINEMATIC,
	BT_DYNAMIC
} jlBodyType;

typedef enum
{
	FM_FORCE,
	FM_IMPLUSE,
	FM_VELOCITY
} jlForceMode;

typedef struct jlBody
{
	jlBodyType type;

	// acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	float mass;
	float inverseMass; // 1 / mass (static = 0)
	float gravityScale;
	float damping;

	float restitution;

	struct jlBody* next;
	struct jlBody* prev;

	Color color;
} jlBody;

inline void ApplyForce(jlBody* body, Vector2 force, jlForceMode forceMode)
{
	if (body->type != BT_DYNAMIC) return;

	switch (forceMode)
	{
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPLUSE:
		// applies a sudden change in momentum
		body->velocity = Vector2Add(body->velocity, Vector2Scale(force, body->inverseMass));
		break;
	case FM_VELOCITY:
		body->velocity = force;
		break;
	}

}

inline void ClearForce(jlBody* body)
{
	body->force = Vector2Zero();
}

void Step(jlBody* body, float timestep);
