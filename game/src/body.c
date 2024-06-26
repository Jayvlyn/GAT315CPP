#include "body.h"
#include "Integrator.h"
#include "world.h"

void Step(jlBody* body, float timestep)
{
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(jlGravity, body->gravityScale), body->mass));
	body->acceleration = Vector2Scale(body->force, body->inverseMass);

	SemiImplicitEuler(body, timestep);

	// apply damping
	float damping = 1 / (1 + (body->damping * timestep));
	body->velocity = Vector2Scale(body->velocity, damping);

	ClearForce(body);
}

