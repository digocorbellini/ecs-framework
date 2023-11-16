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
	ComponentsMask(long mask);
	ComponentsMask(std::initializer_list<ComponentType> list);

	void AddComponent(ComponentType comp);
	void AddComponent(std::initializer_list<ComponentType> list);

	void RemoveComponent(ComponentType comp);
	void RemoveComponent(std::initializer_list<ComponentType> list);

	long GetMask();

	bool operator==(ComponentsMask const& other) const;
	bool operator!=(ComponentsMask const& other) const;
	ComponentsMask operator&(const ComponentsMask& other);

	explicit operator bool() const
	{
		return mask > 0;
	}
};

struct EntityTransform
{
	Vector2f position;
};

struct PhysicsBody
{
	Vector2f velocity;
	bool hasGravity;
	float forceOfGravity;
	RectangleShape bounds;
};

struct Renderer
{
	Sprite sprite;
	Texture texture;
	int renderingOrder;

	/*bool isAnimated;
	float frameRate;*/

	bool isFlipped;

	Renderer()
	{
		sprite = Sprite();
		texture = Texture();
		renderingOrder = 0;
		isFlipped = false;
	}

	struct PointerCompare {
		bool operator()(const Renderer* l, const Renderer* r) {
			return *l < *r;
		}
	};

	bool operator<(const Renderer& other) const
	{
		return renderingOrder < other.renderingOrder;
	}
};

struct PlayerController
{
	float moveSpeed;
	float jumpSpeed;
};
