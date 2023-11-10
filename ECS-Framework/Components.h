#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

enum ComponentType
{
	ENTITY_TRANSFORM,
	PHYSICS_BODY,
	RENDERER,
	PLAYER_CONTROLLER
};

struct EntityTransform
{
	Vector2f position;
};

struct PhysicsBody
{
	float velocity;
	bool hasGravity;
	float forceOfGravity;
	RectangleShape bounds;
};

struct Renderer
{
	Sprite sprite;

	bool isAnimated;
	float frameRate;

	bool isFlipped;
};

struct PlayerController
{
	float moveSpeed;
	float jumpSpeed;
};