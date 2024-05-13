#pragma once

typedef struct jlSpring
{
	struct jlBody* body1;
	struct jlBody* body2;
	float restLength;
	float k; // stiffness

	struct jlSpring* next;
	struct jlSpring* prev;
}jlSpring_t;

extern jlSpring_t* jlSprings;

jlSpring_t* CreateSpring(struct jlBody* body1, struct jlBody* body2, float restLength, float k);
void AddSpring(jlSpring_t* spring);
void DestroySpring(jlSpring_t* spring);
void DestroyAllBodies();

void ApplySpringForce(jlSpring_t* spring);