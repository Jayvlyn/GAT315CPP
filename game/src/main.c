#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "world.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(1200);

	// game loop
	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0))
		{
			CreateBody();
			bodies->position = position;
			bodies->velocity = CreateVector2(GetRandomFloatValue(-100, 100), GetRandomFloatValue(-100, 100));
		}

		BeginDrawing();
		ClearBackground(BLACK);

		// Stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, fps/1000), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.2f", dt), 10, 30, 20, LIME);

		DrawCircle(position.x, position.y, 10, RED);
		// update / draw bodies
		Body* body = bodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// update body position
			body->position = Vector2Add(body->position, Vector2Multiply(body->velocity, CreateVector2(dt, dt)));
			// draw body
			DrawCircle(body->position.x, body->position.y, 10, RED);

			body = body->next; // get next body
		}

		EndDrawing();
	}
	CloseWindow();

	return 0;
}