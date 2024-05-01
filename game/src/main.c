#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "world.h"
#include "Integrator.h"

#include <stdlib.h>
#include <assert.h>

int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0))
		{
			jlBody* body = CreateBody();
			body->position = position;
			body->mass = GetRandomFloatValue(1, 20);
		}

		// apply force
		jlBody* body = jlBodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			ApplyForce(body, CreateVector2(0, -50)); // IF BUG LOWER NUMBERS
			body = body->next; // get next body
		}


		// update bodies
		body = jlBodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// update body position
			ExplicitEuler(body, dt);
			ClearForce(body);
			body = body->next; // get next body
		}

		BeginDrawing();
		ClearBackground(BLACK);

		// Stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, fps/1000), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.2f", dt), 10, 30, 20, LIME);

		
		DrawCircle(position.x, position.y, 10, RED);

		// draw bodies
		body = jlBodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			DrawCircle(body->position.x, body->position.y, body->mass, RED);
			body = body->next; // get next body
		}

		EndDrawing();
	}
	CloseWindow();

	return 0;
}