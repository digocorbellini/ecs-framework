#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <initializer_list>

using namespace sf;

enum ComponentType
{
	ENTITY_TRANSFORM,
	PHYSICS_BODY,
	RENDERER,
	PLAYER_CONTROLLER
};

class ComponentsMask
{
private:
	long mask;

public:
	ComponentsMask();
	ComponentsMask(std::initializer_list<ComponentType> list);

	void AddComponent(ComponentType comp);
	void AddComponent(std::initializer_list<ComponentType> list);

	void RemoveComponent(ComponentType comp);
	void RemoveComponent(std::initializer_list<ComponentType> list);

	long GetMask();

	bool operator==(ComponentsMask const& other) const;
	bool operator!=(ComponentsMask const& other) const;
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
