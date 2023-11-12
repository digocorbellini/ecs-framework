#include "ECS.h"
#include <algorithm>
#include <chrono>
#include <vector>
#include <iostream>

ECS::ECS()
{
	numEntities = 0;
}

ECS::ECS
(
	const Entity* entities,
	const EntityTransform* transforms,
	const PhysicsBody* physicsBodies,
	const Renderer* renderers,
	const PlayerController* playerControllers,
	int size
)
{
	numEntities = std::min(MAX_ENTITIES, size);
	for (int i = 0; i < numEntities; i++) {
		entitiesList[i] = entities[i];
		components.transforms[i] = transforms[i];
		components.physicsBodies[i] = physicsBodies[i];
		components.renderers[i] = renderers[i];
		components.playerControllers[i] = playerControllers[i];
	}
}

bool ECS::AddEntity
(
	Entity entity,
	EntityTransform transform,
	PhysicsBody physicsBody,
	Renderer renderer,
	PlayerController playerController
)
{
	if (numEntities == MAX_ENTITIES) {
		return false;
	}

	entitiesList[numEntities] = entity;
	components.transforms[numEntities] = transform;
	components.physicsBodies[numEntities] = physicsBody;
	components.renderers[numEntities] = renderer;
	components.playerControllers[numEntities] = playerController;
	numEntities++;
	return true;
}

int ECS::AddEntity(ComponentsMask mask)
{
	if (numEntities == MAX_ENTITIES) {
		return false;
	}

	int newIndex = numEntities;
	Entity newEntity;
	newEntity.componentsMask = mask;
	entitiesList[newIndex] = newEntity;
	numEntities++;

	return newIndex;
}

Components* ECS::GetComponents()
{
	return &components;
}

void ECS::GetEntitiesForSystem(ComponentsMask systemMask, int* buffer, int bufferSize)
{
	int count = 0;
	for (int i = 0; i < numEntities && count < bufferSize; ++i)
	{
		Entity currEntity = entitiesList[i];
		if (currEntity.componentsMask & systemMask == systemMask)
		{
			buffer[count] = i;
			count++;
		}
	}

	if (count < bufferSize - 1)
	{
		buffer[count] = -1;
	}
}

void ECS::PhysicsUpdate(double delta)
{

}

void ECS::RenderingUpdate(double delta, RenderWindow& window)
{
	// get all entities that should be rendered
	int entitiesBuffer[MAX_ENTITIES];
	GetEntitiesForSystem(RENDERER_MASK, entitiesBuffer, numEntities);

	// sort all rendering components in order of order in layer
	std::vector<Renderer*> compList;
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		int currID = entitiesBuffer[i];
		if (currID < 0)
			break;

		Renderer* currRend = &components.renderers[currID];

		// perform changes on sprite depending on component values
		currRend->sprite.setOrigin(currRend->texture.getSize().x / 2, currRend->texture.getSize().y / 2);
		currRend->sprite.setPosition(components.transforms[currID].position);
		float xDir = (currRend->isFlipped) ? -1.0f : 1.0f;
		Vector2f newScale = currRend->sprite.getScale();
		newScale.x = abs(newScale.x) * xDir;
		currRend->sprite.setScale(newScale);


		compList.push_back(currRend);
	}
	std::sort(compList.begin(), compList.end(), Renderer::PointerCompare());

	// draw to screen
	window.clear();
	for (int i = 0; i < compList.size(); ++i)
	{
		Renderer* currRend = compList[i];
		window.draw(currRend->sprite);
	}
	window.display();

}

void ECS::MovementUpdate(double delta)
{

}

void ECS::GameLoop()
{
	RenderWindow window(VideoMode(1920, 1080), "SFML works!");
	auto lastTime = std::chrono::high_resolution_clock::now();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		auto time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime =
			std::chrono::duration_cast<std::chrono::duration<double>>(time - lastTime);
		double deltaTime = elapsedTime.count();
		MovementUpdate(deltaTime);
		PhysicsUpdate(deltaTime);
		RenderingUpdate(deltaTime, window);
		lastTime = time;
	}
}