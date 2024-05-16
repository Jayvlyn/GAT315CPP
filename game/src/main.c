#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "world.h"
#include "integrator.h"
#include "firework.h"
#include "force.h"
#include "render.h"
#include "editor.h"
#include "spring.h"
#include "collision.h"
#include "contact.h"

#include <stdlib.h>
#include <assert.h>


int main(void)
{
	jlBody* selectedBody = NULL;
	jlBody* connectBody = NULL;

	InitWindow(1920, 1080, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);

	// initialize world
	jlGravity = (Vector2){ 0, -1 };

	// game loop
	while (!WindowShouldClose())
	{
		// update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		jlGravity = (Vector2){ 0, jlEditorData.GravitySliderValue };

		Vector2 position = GetMousePosition();
		jlScreenZoom += GetMouseWheelMove() * 0.2f;
		jlScreenZoom = Clamp(jlScreenZoom, 0.1, 10);

		UpdateEditor(position);

		selectedBody = GetBodyIntersect(jlBodies, position);
		if (selectedBody)
		{
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selectedBody->mass * 0.5f) + 5, YELLOW);
		}

		if (!jlEditorIntersect)
		{
			// Create body
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)))
			{
				int bodyCount = GetRandomValue(100, 200);
				bodyCount = 1;
				for (int i = 0; i < bodyCount; i++)
				{
					jlBody* body = CreateBody(ConvertScreenToWorld(position), jlEditorData.MassMinSliderValue, jlEditorData.BodyTypeDropdownActive);
					body->damping = 0;//0.5f;
					body->gravityScale = jlEditorData.GravityScaleSliderValue;
					//body->color = ColorFromHSV(0, GetRandomFloatValue01(), GetRandomFloatValue01());
					body->color = WHITE;
					body->restitution = 0.3f;
					AddBody(body);
				}
				//CreateRandomFirework(position);
			}

			// connect spring
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody)
			{
				connectBody = selectedBody;
			}
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody)
			{
				DrawLineBodyToPosition(connectBody, position);
			}
			if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody)
			{
				if (selectedBody && selectedBody != connectBody)
				{
					jlSpring_t* spring = CreateSpring(selectedBody, connectBody, Vector2Distance(selectedBody->position, connectBody->position), 5);
					AddSpring(spring);
				}
			}
		}



		ApplyGravitation(jlBodies, jlEditorData.GravitationSliderValue);
		ApplySpringForce(jlSprings);

		// update bodies
		for (jlBody* body = jlBodies; body; body = body->next)
		{
			Step(body, dt);
		}

		// collision
		jlContact_t* contacts = NULL;
		CreateContacts(jlBodies, &contacts);
		SeparateContacts(contacts);
		ResolveContacts(contacts);


		// render
		BeginDrawing();
		ClearBackground(BLACK);



		// Stats
		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, fps/1000), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.2f", dt), 10, 30, 20, LIME);

		
		//DrawCircle(position.x, position.y, 10, RED);

		// draw bodies
		for (jlBody* body = jlBodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle(screen.x, screen.y, ConvertWorldToPixel(body->mass * 0.5f), body->color);
		}
		// draw springs
		for (jlSpring_t* spring = jlSprings; spring; spring = spring->next)
		{
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine(screen1.x, screen1.y, screen2.x, screen2.y, YELLOW);
		}
		// draw contacts
		for (jlContact_t* contact = contacts; contact; contact = contact->next)
		{
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle(screen.x, screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), RED);
		}

		DrawEditor(position);

		EndDrawing();
	}
	CloseWindow();

	return 0;
}

