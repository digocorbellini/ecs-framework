#include "ECS.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int GRAV = 300;
const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;

ECS ecs;

int Benchmark()
{
    Components* components = ecs.GetComponents();
    int newEntityID;
    Vector2f pos;

    // create falling boxes
    Texture boxTexture = Texture();
    boxTexture.loadFromFile("./poggies.png");
    Sprite boxSprite = Sprite(boxTexture);
    boxSprite.setScale(Vector2f(0.02f, 0.02f));
    for (int i = 0; i < 5000; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = boxTexture;
        components->renderers[newEntityID].sprite = boxSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(1000 - (15 * i), 300 - (20 * i));
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(15, 20));
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

    ecs.GameLoop();

    return 0;
}

int Game() {
   Components* components = ecs.GetComponents();
   int newEntityID;
   Vector2f pos;

   // create player
   int playerEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::PLAYER_CONTROLLER, ComponentType::PHYSICS_BODY, ComponentType::RENDERER }));
   components->renderers[playerEntityID].texture = Texture();
   components->renderers[playerEntityID].texture.loadFromFile("./poggies.png");
   components->renderers[playerEntityID].sprite = Sprite(components->renderers[playerEntityID].texture);
   components->renderers[playerEntityID].sprite.setScale(Vector2f(0.1f, 0.1f));
   components->renderers[playerEntityID].isFlipped = true;
   components->playerControllers[playerEntityID].moveSpeed = 300;
   components->playerControllers[playerEntityID].jumpSpeed = 200;
   pos = Vector2f(1000, 300);
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
   components->cameras[newEntityID].viewOffsetFromPos = Vector2f(0, -100);

    // create ground
   newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
   components->renderers[newEntityID].texture = Texture();
   components->renderers[newEntityID].texture.loadFromFile("./poggies.png");
   components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
   components->renderers[newEntityID].sprite.setScale(Vector2f(2.0f, 0.2f));
   components->renderers[newEntityID].isFlipped = false;
   components->renderers[newEntityID].renderingOrder = 1;
   pos = Vector2f(900, 800);
   components->transforms[newEntityID].position = pos;
   components->physicsBodies[newEntityID].velocity = Vector2f(0, 0);
   components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
   components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(1500, 200));
   components->physicsBodies[newEntityID].hasGravity = false;
   components->physicsBodies[newEntityID].isStatic = true;
   components->physicsBodies[newEntityID].isOnGround = false;

   // create static wall
   newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
   components->renderers[newEntityID].texture = Texture();
   components->renderers[newEntityID].texture.loadFromFile("./poggies.png");
   components->renderers[newEntityID].sprite = Sprite(components->renderers[newEntityID].texture);
   components->renderers[newEntityID].sprite.setScale(Vector2f(1.0f, 1.0f));
   components->renderers[newEntityID].isFlipped = false;
   components->renderers[newEntityID].renderingOrder = 1;
   pos = Vector2f(1500, 200);
   components->transforms[newEntityID].position = pos;
   components->physicsBodies[newEntityID].velocity = Vector2f(0, 0);
   components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
   components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(750, 1000));
   components->physicsBodies[newEntityID].hasGravity = false;
   components->physicsBodies[newEntityID].isStatic = true;
   components->physicsBodies[newEntityID].isOnGround = false;

   ecs.GameLoop();

   return 0;
}

int main()
{

    //Benchmark();
    Game();

    return 0;
}