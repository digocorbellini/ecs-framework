#include "ECS.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

using namespace sf;
using namespace std;


int main()
{
    ECS ecs;

    Components* components = ecs.GetComponents();

    // TODO: remove these examples of drawing to the screen by creating entities
    int newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER }));
    components->renderers[newEntityID].texture = Texture();
    components->renderers[newEntityID].texture.loadFromFile("./poggies.png");
    components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
    components->renderers[newEntityID].sprite.setPosition(Vector2f(50, 50));
    components->renderers[newEntityID].sprite.setScale(Vector2f(0.5f, 0.5f));
    components->renderers[newEntityID].isFlipped = false;
    components->renderers[newEntityID].renderingOrder = 1;
    components->transforms[newEntityID].position = Vector2f(200, 250);

    newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::PLAYER_CONTROLLER, ComponentType::PHYSICS_BODY, ComponentType::RENDERER }));
    components->renderers[newEntityID].texture = Texture();
    components->renderers[newEntityID].texture.loadFromFile("./poggies.png");
    components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
    components->renderers[newEntityID].sprite.setPosition(Vector2f(50, 50));
    components->renderers[newEntityID].sprite.setScale(Vector2f(0.5f, 0.5f));
    components->renderers[newEntityID].isFlipped = true;
    components->transforms[newEntityID].position = Vector2f(300, 300);
    components->playerControllers[newEntityID].moveSpeed = 100;
    components->playerControllers[newEntityID].jumpSpeed = 100;

    ecs.GameLoop();

    return 0;
}