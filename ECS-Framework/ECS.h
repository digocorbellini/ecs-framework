#pragma once

#include "Components.h"

using namespace sf;

#define MAX_ENTITIES 30

const ComponentsMask PHYSICS_MASK({ ComponentType::ENTITY_TRANSFORM, ComponentType::PHYSICS_BODY });
const ComponentsMask RENDERER_MASK({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER });
const ComponentsMask CONTROLLER_MASK({ ComponentType::ENTITY_TRANSFORM, ComponentType::PLAYER_CONTROLLER });

// Systems will operate on this struct of all components in the game
struct Components
{
	// Every entity has an entry in every list. Their component is
	// accessed by indexing using their entity id;
	EntityTransform transforms[MAX_ENTITIES];
	PhysicsBody physicsBodies[MAX_ENTITIES];
	Renderer renderers[MAX_ENTITIES];
	PlayerController playerControllers[MAX_ENTITIES];
};

struct Entity
{
	ComponentsMask componentsMask;
};

class ECS
{
private:
	int numEntities;
	Entity entitiesList[MAX_ENTITIES];
	Components components;

	void PhysicsUpdate(double delta);
	void RenderingUpdate(double delta, RenderWindow& window);
	void MovementUpdate(double delta);
public:
	ECS();
	ECS
	(
		const Entity* entities,
		const EntityTransform* transforms,
		const PhysicsBody* physicsBodies,
		const Renderer* renderers,
		const PlayerController* playerControllers,
		int size
	);

	bool AddEntity
	(
		Entity entity,
		EntityTransform transform,
		PhysicsBody physicsBody,
		Renderer renderer,
		PlayerController playerController
	);

	void GameLoop();
};