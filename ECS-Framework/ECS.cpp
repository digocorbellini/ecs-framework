#include "ECS.h"
#include <algorithm>
#include <chrono>

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

void ECS::PhysicsUpdate(double delta)
{

}

void ECS::RenderingUpdate(double delta, RenderWindow& window)
{
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);
	window.clear();
	window.draw(shape);
	window.display();
}

void ECS::MovementUpdate(double delta)
{

}

void ECS::GameLoop()
{
	RenderWindow window(VideoMode(200, 200), "SFML works!");
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