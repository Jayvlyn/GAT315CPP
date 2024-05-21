#include "world.h"
#include "body.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

jlBody* jlBodies = NULL;
int jlBodyCount = 0;
Vector2 jlGravity;

jlBody* CreateBody(Vector2 position, float mass, jlBodyType bodyType) 
{
	//Allocate memory for new Body
	jlBody* body = (jlBody*)malloc(sizeof(jlBody));

	//Check if allocation is successful
	assert(body);

	memset(body, 0, sizeof(jlBody));
	body->position = position;
	body->mass = mass;
	body->inverseMass = (bodyType == BT_DYNAMIC) ? 1 / mass : 0; // static and kinematic have no inverse mass
	body->type = bodyType;
	
	return body;
}

void AddBody(jlBody* body)
{
	assert(body);

	//Initialize 'prev' to NULL and 'next' to the head of the list
	body->prev = NULL;
	body->next = jlBodies;

	//If list is not empty, update 'prev' of existing head
	if (jlBodies) jlBodies->prev = body;

	// set head of elements to new elemnt
	jlBodies = body;

	//Increment body count
	jlBodyCount++;

	//Return new Body
	return body;
}

void DestroyBody(jlBody* body)
{
	//Assert if provided Body is not NULL
	assert(body);

	//If 'prev' is not NULL, set 'prev->next' to 'body->next'
	if (body->prev != NULL) body->prev->next = body->next;

	//If 'next' is not NULL, set 'next->prev' to 'body->prev'
	if (body->next != NULL) body->next->prev = body->prev;

	//If body is the head, update head to 'body->next'
	if (body == jlBodies) jlBodies = body->next;

	//Decrement body count
	jlBodyCount--;
	
	//Free the body
	free(body);
}

void DestroyAllBodies()
{
	if (!jlBodies) return;
	jlBody* body = jlBodies;
	jlBody* temp;

	while (body)
	{
		temp = body->next;
		free(body);
		body = temp;
	}
	jlBodies = NULL;
}