#include "world.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

jlBody* jlBodies = NULL;
int jlBodyCount = 0;

jlBody* CreateBody() 
{
	//Allocate memory for new Body
	jlBody* body = (jlBody*)malloc(sizeof(jlBody));

	//Check if allocation is successful
	assert(body);

	memset(body, 0, sizeof(jlBody));
	
	//Initialize 'prev' to NULL and 'next' to the head of the list
	body->prev = NULL;
	body->next = jlBodies;

	//If list is not empty, update 'prev' of existing head
	if (jlBodies != NULL)
	{
		jlBodies->prev = body;
	}

	//Update head of the list to new Body
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