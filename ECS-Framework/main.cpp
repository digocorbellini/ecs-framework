#include "ECS.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int GRAV = 300;
const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

ECS ecs;

int main()
{

    Components* components = ecs.GetComponents();
    int newEntityID;
    Vector2f pos;

    /*// create player
    int playerEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::PLAYER_CONTROLLER, ComponentType::PHYSICS_BODY, ComponentType::RENDERER }));
    components->renderers[playerEntityID].texture = Texture();
    components->renderers[playerEntityID].texture.loadFromFile("./poggies.png");
    components->renderers[playerEntityID].sprite = Sprite(components->renderers[playerEntityID].texture);
    components->renderers[playerEntityID].sprite.setScale(Vector2f(0.1f, 0.1f));
    components->renderers[playerEntityID].isFlipped = true;
    components->playerControllers[playerEntityID].moveSpeed = 500;
    components->playerControllers[playerEntityID].jumpSpeed = 200;
    Vector2f pos = Vector2f(1000, 300);
    components->transforms[playerEntityID].position = pos;
    components->physicsBodies[playerEntityID].velocity = Vector2f(0, 0);
    components->physicsBodies[playerEntityID].gravityAccel = Vector2f(0, GRAV);
    components->physicsBodies[playerEntityID].bounds = Rect<float>(pos, Vector2f(75, 100));
    components->physicsBodies[playerEntityID].hasGravity = true;
    components->physicsBodies[playerEntityID].isStatic = false;
    components->physicsBodies[playerEntityID].isOnGround = false;

     // create camera
    newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::CAMERA }));
    components->cameras[newEntityID].targetTransform = &components->transforms[playerEntityID];
    components->cameras[newEntityID].isMainCam = true;
    components->cameras[newEntityID].cameraView = View(FloatRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_HEIGHT, SCREEN_HEIGHT));
    components->cameras[newEntityID].viewOffsetFromPos = Vector2f(0, -100);*/

    // create falling box
    Texture boxTexture = Texture();
    boxTexture.loadFromFile("./poggies.png");
    for (int i = 0; i < 5000; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = boxTexture;
        components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
        components->renderers[newEntityID].sprite.setScale(Vector2f(0.1f, 0.1f));
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(1000 - (75 * i), 300 - (100 * i));
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(200, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(75, 100));
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = false;
        components->physicsBodies[newEntityID].isOnGround = false;
    }


    // create static ground
    newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
    components->renderers[newEntityID].texture = Texture();
    components->renderers[newEntityID].texture.loadFromFile("./poggies.png");
    components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
    components->renderers[newEntityID].sprite.setScale(Vector2f(1.0f, 0.2f));
    components->renderers[newEntityID].isFlipped = false;
    components->renderers[newEntityID].renderingOrder = 1;
    pos = Vector2f(900, 800);
    components->transforms[newEntityID].position = pos;
    components->physicsBodies[newEntityID].velocity = Vector2f(0, 0);
    components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
    components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(750, 200));
    components->physicsBodies[newEntityID].hasGravity = false;
    components->physicsBodies[newEntityID].isStatic = true;
    components->physicsBodies[newEntityID].isOnGround = false;

    // create static wall, demonstrate alternate way of adding entity



    ecs.GameLoop();   

    return 0;
}