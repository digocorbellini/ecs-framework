#include "ECS.h"
#include <algorithm>
#include <chrono>
#include <vector>
#include <iostream>

ECS::ECS()
{
	numEntities = 0;
	backgroundColor = Color(0, 0, 0, 255);
	isDebugMode = false;
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
	numEntities = 0;
	backgroundColor = Color(0, 0, 0, 255);
	isDebugMode = false;

	numEntities = std::min(MAX_ENTITIES, size);
	for (int i = 0; i < numEntities; i++)
	{
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
	if (numEntities == MAX_ENTITIES)
	{
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
	if (numEntities == MAX_ENTITIES)
	{
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

void ECS::SetBackgroundColor(Color color)
{
	backgroundColor = color;
}

Color ECS::GetBackgroundColor()
{
	return backgroundColor;
}

void ECS::SetDebugMode(bool isDebug)
{
	isDebugMode = isDebug;
}

bool ECS::GetDebugMode()
{
	return isDebugMode;
}

void ECS::PhysicsUpdate(float delta)
{
	for (int i = 0; i < numEntities; i++)
	{
		Entity currEntity = entitiesList[i];
		if ((currEntity.componentsMask & PHYSICS_MASK) != PHYSICS_MASK)
		{
			continue;
		}
		EntityTransform* currTransform = &components.transforms[i];
		PhysicsBody* currPhysics = &components.physicsBodies[i];
		if (!currPhysics->isStatic)
		{
			// use velocity verlet to update position and velocity
			currPhysics->oldPosition = currTransform->position;
			currTransform->position += currPhysics->velocity * delta;
			currPhysics->oldVelocity = currPhysics->velocity;
			if (currPhysics->hasGravity)
			{
				currPhysics->velocity += currPhysics->gravityAccel * delta;
			}
		}
		currPhysics->isOnGround = false;
		currPhysics->bounds.left = currTransform->position.x - (currPhysics->bounds.width / 2.0f);
		currPhysics->bounds.top = currTransform->position.y - (currPhysics->bounds.height / 2.0f);
	}
	// detect and resolve collisions
	for (int i = 0; i < numEntities; i++)
	{
		Entity currEntity = entitiesList[i];
		if (((currEntity.componentsMask & PHYSICS_MASK) != PHYSICS_MASK))
		{
			continue;
		}
		EntityTransform* currTransform = &components.transforms[i];
		PhysicsBody* currPhysics = &components.physicsBodies[i];
		if (!currPhysics->isStatic) // only resolve dynamic objects
		{
			int firstIntersectIndex = -1;
			float firstIntersectTime = FLT_MAX;
			for (int j = 0; j < numEntities; j++)
			{
				Entity pairEntity = entitiesList[j];
				if (((pairEntity.componentsMask & PHYSICS_MASK) != PHYSICS_MASK) || j == i)
				{
					continue;
				}
				PhysicsBody* pairPhysics = &components.physicsBodies[j];
				if (pairPhysics->isStatic) // only dynamic -> static body collisions are handled
				{
					// swept collision detection
					// calculate time of intersection (TOI) and time of exit (TOE) on each axis separately
					// TOI is calculated by getting penetration time (penetration distance divided by velocity) and subtracting that from delta
					float xTOI;
					float xTOE;
					if (currPhysics->oldVelocity.x > 0.0f)
					{
 						xTOI = delta - (((currPhysics->bounds.left + currPhysics->bounds.width) - pairPhysics->bounds.left) / currPhysics->oldVelocity.x);
						xTOE = delta - ((currPhysics->bounds.left - (pairPhysics->bounds.left + pairPhysics->bounds.width)) / currPhysics->oldVelocity.x);
					}
					else if (currPhysics->oldVelocity.x < 0.0f)
					{
						xTOI = delta - (((pairPhysics->bounds.left + pairPhysics->bounds.width) - currPhysics->bounds.left) / -currPhysics->oldVelocity.x);
						xTOE = delta - ((pairPhysics->bounds.left - (currPhysics->bounds.left + currPhysics->bounds.width)) / -currPhysics->oldVelocity.x);
					}
					else
					{
						if ((currPhysics->bounds.left + currPhysics->bounds.width) > pairPhysics->bounds.left && currPhysics->bounds.left < (pairPhysics->bounds.left + pairPhysics->bounds.width)) // already overlapping
						{
							xTOI = 0.0f;
							xTOE = FLT_MAX;
						}
						else
						{
							xTOI = FLT_MAX;
							xTOE = 0.0f;
						}
					}
					float yTOI;
					float yTOE;
					if (currPhysics->oldVelocity.y > 0.0f)
					{
						yTOI = delta - (((currPhysics->bounds.top + currPhysics->bounds.height) - pairPhysics->bounds.top) / currPhysics->oldVelocity.y);
						yTOE = delta - ((currPhysics->bounds.top - (pairPhysics->bounds.top + pairPhysics->bounds.height)) / currPhysics->oldVelocity.y);
					}
					else if (currPhysics->oldVelocity.y < 0.0f)
					{
						yTOI = delta - (((pairPhysics->bounds.top + pairPhysics->bounds.height) - currPhysics->bounds.top) / -currPhysics->oldVelocity.y);
						yTOE = delta - ((pairPhysics->bounds.top - (currPhysics->bounds.top + currPhysics->bounds.height)) / -currPhysics->oldVelocity.y);
					}
					else
					{
						if ((currPhysics->bounds.top + currPhysics->bounds.height) > pairPhysics->bounds.top && currPhysics->bounds.top < (pairPhysics->bounds.top + pairPhysics->bounds.height))
						{
							yTOI = 0.0f;
							yTOE = FLT_MAX;
						}
						else
						{
							yTOI = FLT_MAX;
							yTOE = 0.0f;
						}
					}
					float TOI = std::max(xTOI, yTOI); // for a collision to occur, both axes must collide, so we take the later axis TOI
					float TOE = std::min(xTOE, yTOE); // inverse argument of TOI
					if (TOI > delta || TOE <= 0.0f || TOI > TOE) // implies intersection didn't occur
					{
						continue;
					}
					if (TOE <= delta) // if object can exit in one frame, just let it
					{
						continue;
					}
					// TODO: only process first intersection, reprocess intersections after deflection

					// calculate normals to slide
					Vector2f collisionNormal;
					if (xTOI > yTOI) // collision happens on x axis
					{
						if (currPhysics->oldVelocity.x > 0.0f)
						{
							collisionNormal = Vector2f(-1, 0);
						}
						else
						{
							collisionNormal = Vector2f(1, 0);
						}
					}
					else
					{
						if (currPhysics->oldVelocity.y > 0.0f)
						{
							collisionNormal = Vector2f(0, -1);
							currPhysics->isOnGround = true;
						}
						else
						{
							collisionNormal = Vector2f(0, 1);
						}
					}
					// move object to TOI with slight offset away from surface for float precision
					currTransform->position -= currPhysics->oldVelocity * (delta - TOI);
					currTransform->position += 0.01f * collisionNormal;
					// cancel out velocity going into the collision surface with vector projection
					currPhysics->velocity -= (currPhysics->velocity.x * collisionNormal.x + currPhysics->velocity.y * collisionNormal.y) * collisionNormal;
					currPhysics->bounds.left = currTransform->position.x - (currPhysics->bounds.width / 2.0f);
					currPhysics->bounds.top = currTransform->position.y - (currPhysics->bounds.height / 2.0f);
				}
			}
		}
	}
}

void ECS::RenderingUpdate(float delta, RenderWindow& window)
{
	// sort all rendering components in order of order in layer
	std::vector<Renderer*> compList;
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		Entity currEntity = entitiesList[i];
		if ((currEntity.componentsMask & RENDERER_MASK) != RENDERER_MASK)
		{
			continue;
		}

		Renderer* currRend = &components.renderers[i];

		// perform changes on sprite depending on component values
		currRend->sprite.setOrigin(currRend->texture.getSize().x / 2, currRend->texture.getSize().y / 2);
		currRend->sprite.setPosition(components.transforms[i].position);
		float xDir = (currRend->isFlipped) ? -1.0f : 1.0f;
		Vector2f newScale = currRend->sprite.getScale();
		newScale.x = abs(newScale.x) * xDir;
		currRend->sprite.setScale(newScale);


		compList.push_back(currRend);
	}
	std::sort(compList.begin(), compList.end(), Renderer::PointerCompare());

	// draw to screen
	window.clear(backgroundColor);
	for (int i = 0; i < compList.size(); ++i)
	{
		Renderer* currRend = compList[i];
		window.draw(currRend->sprite);
	}
	window.display();

}

void ECS::MovementUpdate(float delta, Event event)
{
	for (int i = 0; i < numEntities; ++i)
	{
		Entity currEntity = entitiesList[i];
		if ((currEntity.componentsMask & CONTROLLER_MASK) != CONTROLLER_MASK)
		{
			continue;
		}

		EntityTransform* currTransform = &components.transforms[i];
		PhysicsBody* currPhysics = &components.physicsBodies[i];
		PlayerController* currController = &components.playerControllers[i];

		// player movement 
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			// go left
			currPhysics->velocity.x = -currController->moveSpeed;
			components.renderers[i].isFlipped = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			// go right
			currPhysics->velocity.x = currController->moveSpeed;
			components.renderers[i].isFlipped = false;
		}
		else
		{
			currPhysics->velocity.x = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && currPhysics->isOnGround)
		{
			// jump
			currPhysics->velocity.y = -currController->jumpSpeed;
		}
	}
}

void ECS::CameraUpdate(float delta, RenderWindow& window)
{
	for (int i = 0; i < numEntities; ++i)
	{
		Entity currEntity = entitiesList[i];
		if ((currEntity.componentsMask & CAMERA_MASK) != CAMERA_MASK)
		{
			continue;
		}

		Camera* currCamera = &components.cameras[i];
		EntityTransform* currTransform = &components.transforms[i];
		if (currCamera->targetTransform != NULL)
		{
			currTransform->position = currCamera->targetTransform->position;
		}

		currCamera->cameraView.setCenter(currTransform->position + currCamera->viewOffsetFromPos);
		if (currCamera->isMainCam)
		{
			window.setView(currCamera->cameraView);
		}
	}
}

void ECS::GameLoop()
{
	RenderWindow window(VideoMode(1920, 1080), "ECS Demo");
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
			std::chrono::duration_cast<std::chrono::duration<float>>(time - lastTime);
		float deltaTime = elapsedTime.count();

		if (isDebugMode)
		{
			std::cout << (1.0f / deltaTime) << std::endl;
		}

		MovementUpdate(deltaTime, event);
		PhysicsUpdate(deltaTime);
		CameraUpdate(deltaTime, window);
		RenderingUpdate(deltaTime, window);
		lastTime = time;
	}
}