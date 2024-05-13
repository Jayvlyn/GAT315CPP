#pragma once
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"
#include "world.h"
#include "Integrator.h"

#include <stdlib.h>
#include <assert.h>


void CircleFirework(Vector2 position)
{
	int bodyCount = GetRandomValue(50, 100);
	for (int i = 0; i < bodyCount; i++)
	{
		jlBody* body = CreateBody(position, GetRandomFloatValue(1, 20), BT_DYNAMIC);
		body->damping = 0.5f;
		body->gravityScale = 20;
		body->color = ColorFromHSV(GetRandomFloatValue(0, 255), 0.5, 1);
		//ApplyForce(body, (Vector2) {GetRandomFloatValue(-400, 400), GetRandomFloatValue(-400, 400) }, FM_VELOCITY);
		#pragma region Phind assisted circular generation
		float angle = GetRandomFloatValue(0, 360);
		float angleRadians = angle * (PI / 180.0f);
		float radius = GetRandomFloatValue(200, 400);
		Vector2 force = { radius * cos(angleRadians), radius * sin(angleRadians) };
		#pragma endregion
		ApplyForce(body, force, FM_VELOCITY);
	}
}

void MonochromeCircleFirework(Vector2 position, int hue)
{
	int bodyCount = GetRandomValue(50, 100);
	for (int i = 0; i < bodyCount; i++)
	{
		jlBody* body = CreateBody(position, GetRandomFloatValue(1, 20), BT_DYNAMIC);
		body->damping = 0.5f;
		body->gravityScale = 20;
		body->color = ColorFromHSV(hue, GetRandomFloatValue01(), GetRandomFloatValue01());
		//ApplyForce(body, (Vector2) {GetRandomFloatValue(-400, 400), GetRandomFloatValue(-400, 400) }, FM_VELOCITY);
#pragma region Phind assisted circular generation
		float angle = GetRandomFloatValue(0, 360);
		float angleRadians = angle * (PI / 180.0f);
		float radius = GetRandomFloatValue(200, 400);
		Vector2 force = { radius * cos(angleRadians), radius * sin(angleRadians) };
#pragma endregion
		ApplyForce(body, force, FM_VELOCITY);
	}
}

void SquareFirework(Vector2 position)
{
	int bodyCount = GetRandomValue(100, 200);
	for (int i = 0; i < bodyCount; i++)
	{
		jlBody* body = CreateBody(position, GetRandomFloatValue(1, 20), BT_DYNAMIC);
		body->damping = 0.5f;
		body->gravityScale = 20;
		body->color = ColorFromHSV(0, GetRandomFloatValue01(), GetRandomFloatValue01());
		Vector2 force = { GetRandomFloatValue(-400, 400), GetRandomFloatValue(-400, 400) };
		ApplyForce(body, force, FM_VELOCITY);
	}
}

void CreateRandomFirework(Vector2 position)
{
	int pick = GetRandomValue(0, 2);
	switch (pick)
	{
	case 0:
		CircleFirework(position);
		break;
	case 1:
		SquareFirework(position);
		break;
	case 2:
		MonochromeCircleFirework(position, GetRandomValue(0, 255));
		break;
	case 3:
		break;
	}


}