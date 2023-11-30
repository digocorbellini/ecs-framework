#include "ECS.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int GRAV = 300;

int main()
{
    ECS ecs;

    Components* components = ecs.GetComponents();

    int newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::PLAYER_CONTROLLER, ComponentType::PHYSICS_BODY, ComponentType::RENDERER }));
    components->renderers[newEntityID].texture = Texture();
    components->renderers[newEntityID].texture.loadFromFile("./poggies.png");
    components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
    components->renderers[newEntityID].sprite.setScale(Vector2f(0.1f, 0.1f));
    components->renderers[newEntityID].isFlipped = true;
    components->playerControllers[newEntityID].moveSpeed = 500;
    components->playerControllers[newEntityID].jumpSpeed = 100;
    Vector2f pos = Vector2f(1000, 300);
    components->transforms[newEntityID].position = pos;
    components->physicsBodies[newEntityID].velocity = Vector2f(0, 0);
    components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
    components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(75, 100));
    components->physicsBodies[newEntityID].hasGravity = true;
    components->physicsBodies[newEntityID].isStatic = false;
    components->physicsBodies[newEntityID].isOnGround = false;

    newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
    components->renderers[newEntityID].texture = Texture();
    components->renderers[newEntityID].texture.loadFromFile("./poggies.png");
    components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
    components->renderers[newEntityID].sprite.setScale(Vector2f(2.0f, 0.2f));
    components->renderers[newEntityID].isFlipped = false;
    components->renderers[newEntityID].renderingOrder = 1;
    pos = Vector2f(900, 500);
    components->transforms[newEntityID].position = pos;
    components->physicsBodies[newEntityID].velocity = Vector2f(0, 0);
    components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
    components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(1500, 200));
    components->physicsBodies[newEntityID].hasGravity = false;
    components->physicsBodies[newEntityID].isStatic = true;
    components->physicsBodies[newEntityID].isOnGround = false;

    ecs.GameLoop();   

    return 0;
}