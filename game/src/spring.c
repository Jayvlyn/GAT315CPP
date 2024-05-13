#include "spring.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

jlSpring_t* jlSprings = NULL;

jlSpring_t* CreateSpring(struct jlBody* body1, struct jlBody* body2, float restLength, float k)
{
	jlSpring_t* spring = (jlSpring_t*)malloc(sizeof(jlSpring_t));
	assert(spring);

	memset(spring, 0, sizeof(jlSpring_t));
	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;

	return spring;
}

void AddSpring(jlSpring_t* spring)
{
	assert(spring);

	spring->prev = NULL;
	spring->next = jlSprings;

	//If list is not empty, update 'prev' of existing head
	if (jlSprings) jlSprings->prev = spring;

	// set head of elements to new elemnt
	jlSprings = spring;
}

void DestroySpring(jlSpring_t* spring)
{
	assert(spring);

	if (spring->prev != NULL) spring->prev->next = spring->next;
	if (spring->next != NULL) spring->next->prev = spring->prev;

	if (spring == jlSprings) jlSprings = spring->next;

	free(spring);
}

void ApplySpringForce(jlSpring_t* springs)
{
	for (jlSpring_t* spring = springs; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body2->position,spring->body1->position);
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength;
		float force = x * spring->k;

		Vector2 ndirection = Vector2Normalize(direction);

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(ndirection, -force), FM_FORCE);
	}
}