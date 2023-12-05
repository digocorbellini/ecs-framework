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

    ecs.SetDebugMode(false);

    // create falling boxes
    Texture boxTexture = Texture();
    boxTexture.loadFromFile("./poggies.png");
    Sprite boxSprite = Sprite(boxTexture);
    boxSprite.setScale(Vector2f(0.05f, 0.05f));
    for (int i = 0; i < 500; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = boxTexture;
        components->renderers[newEntityID].sprite = boxSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(-800 + (50 * i), -100);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(15, 20));
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = false;
        components->physicsBodies[newEntityID].isOnGround = false;

        for (int x = 1; x <= 10; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = boxTexture;
            components->renderers[newEntityID].sprite = boxSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f newBos = pos + Vector2f(-50 * x, 60 * x);
            components->transforms[newEntityID].position = newBos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(pos, Vector2f(15, 20));
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = false;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
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
   components->cameras[newEntityID].cameraView = View(FloatRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT));
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

void TechDemo()
{
    Components* components = ecs.GetComponents();
    int newEntityID;
    Vector2f pos;

    ecs.SetBackgroundColor(Color(207, 239, 252, 255));
    ecs.SetDebugMode(false);

    // load images
    Texture grassTexture = Texture();
    grassTexture.loadFromFile("./Images/grass_tile.png");
    Sprite grassSprite = Sprite(grassTexture);

    Texture dirtTexture = Texture();
    dirtTexture.loadFromFile("./Images/dirt_tile.png");
    Sprite dirtSprite = Sprite(dirtTexture);

    Texture platTexture = Texture();
    platTexture.loadFromFile("./Images/plat_tile.png");
    Sprite platSprite = Sprite(platTexture);

    Texture backgroundTexture = Texture();
    backgroundTexture.loadFromFile("./Images/background.png");
    Sprite backgroundSprite = Sprite(backgroundTexture);

    Texture brickTexture = Texture();
    brickTexture.loadFromFile("./Images/brick_tile.png");
    Sprite brickSprite = Sprite(brickTexture);

    Texture doorwayTexture = Texture();
    doorwayTexture.loadFromFile("./Images/doorway_tile.png");
    Sprite doorwaySprite = Sprite(doorwayTexture);
    doorwaySprite.setScale(2, 2);

    Texture boxTexture = Texture();
    boxTexture.loadFromFile("./Images/box_tile.png");
    Sprite boxSprite = Sprite(boxTexture);

    // create backgrounds
    for (int i = 0; i < 20; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER }));
        components->renderers[newEntityID].texture = backgroundTexture;
        components->renderers[newEntityID].sprite = backgroundSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 0;
        pos = Vector2f(-512 + (512 * 2 * i), 800 - (64 * 8));
        components->transforms[newEntityID].position = pos;
    }

    // create grass wall to the left of spawn
    for (int i = 0; i < 20; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(220 - (64 * i), 800 - (64 * 5));
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 20; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create initial flat space
    for (int i = 0; i < 20; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(1500 - (64 * i), 800);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 10; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create a little platforming hump
    for (int i = 0; i < 10; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(1500 + (64 * i), 800 - 64);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 15; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create a flat space under some platforms
    for (int i = 0; i < 25; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(2140 + (64 * i), 800);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 10; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create 3 floating platforms
    Vector2f startingPos(2140 + (64 * 3), 800 - (64 * 3));
    for (int i = 0; i < 3; i++)
    {
        // create platform under the grass
        for (int x = 0; x < 3; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = platTexture;
            components->renderers[newEntityID].sprite = platSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            if (x != 0)
                startingPos += Vector2f(64, 0);
            components->transforms[newEntityID].position = startingPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(platSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }

        startingPos += Vector2f(64 * 4, 0);
    }

    // create a little platforming hump
    for (int i = 0; i < 10; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(2140 + (64 * 25) + (64 * i), 800 - 64);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 15; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create a little platforming hump
    for (int i = 0; i < 15; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(2140 + (64 * 35) + (64 * i), 800 - 128);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 15; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create a little platforming hump
    Vector2f lastAreaStart = pos;
    for (int i = 0; i < 30; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos += Vector2f(64, 0);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 15; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create ending castle
    pos = lastAreaStart + Vector2f(64 * 0, -64);
    for (int i = 0; i < 7; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER}));
        components->renderers[newEntityID].texture = brickTexture;
        components->renderers[newEntityID].sprite = brickSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos += Vector2f(64, 0);
        components->transforms[newEntityID].position = pos;

        if (i == 3)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER }));
            components->renderers[newEntityID].texture = doorwayTexture;
            components->renderers[newEntityID].sprite = doorwaySprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 2;
            components->transforms[newEntityID].position = pos + Vector2f(0, -32);
        }
        
        // create dirt under the grass
        for (int x = 1; x <= 4; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER }));
            components->renderers[newEntityID].texture = brickTexture;
            components->renderers[newEntityID].sprite = brickSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, -64 * x);
            components->transforms[newEntityID].position = dirtPos;
        }
    }

    // use blocks to hide player to show off rendering layers
    pos = lastAreaStart + Vector2f(64 * -7, -64);
    for (int i = 0; i < 7; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER }));
        components->renderers[newEntityID].texture = boxTexture;
        components->renderers[newEntityID].sprite = boxSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 20;
        pos += Vector2f(64, 0);
        components->transforms[newEntityID].position = pos;
    }


    // create player
    int playerEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::PLAYER_CONTROLLER, ComponentType::PHYSICS_BODY, ComponentType::RENDERER }));
    components->renderers[playerEntityID].texture = Texture();
    components->renderers[playerEntityID].texture.loadFromFile("./poggies.png");
    components->renderers[playerEntityID].sprite = Sprite(components->renderers[playerEntityID].texture);
    components->renderers[playerEntityID].sprite.setScale(Vector2f(0.1f, 0.1f));
    components->renderers[playerEntityID].isFlipped = true;
    components->renderers[playerEntityID].renderingOrder = 10;
    components->playerControllers[playerEntityID].moveSpeed = 500;
    components->playerControllers[playerEntityID].jumpSpeed = 600;
    pos = Vector2f(1000, 500);
    components->transforms[playerEntityID].position = pos;
    components->physicsBodies[playerEntityID].velocity = Vector2f(0, 0);
    components->physicsBodies[playerEntityID].gravityAccel = Vector2f(0, GRAV * 3);
    components->physicsBodies[playerEntityID].bounds = Rect<float>(components->renderers[playerEntityID].sprite.getGlobalBounds());
    components->physicsBodies[playerEntityID].hasGravity = true;
    components->physicsBodies[playerEntityID].isStatic = false;
    components->physicsBodies[playerEntityID].isOnGround = false;

    // create camera
    newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::CAMERA }));
    components->cameras[newEntityID].targetTransform = &components->transforms[playerEntityID];
    components->cameras[newEntityID].isMainCam = true;
    components->cameras[newEntityID].cameraView = View(FloatRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT));
    components->cameras[newEntityID].viewOffsetFromPos = Vector2f(0, -100);

    ecs.GameLoop();
}

void BoxDrop()
{
    Components* components = ecs.GetComponents();
    int newEntityID;
    Vector2f pos;

    ecs.SetBackgroundColor(Color(207, 239, 252, 255));
    ecs.SetDebugMode(true);

    // load images
    Texture grassTexture = Texture();
    grassTexture.loadFromFile("./Images/grass_tile.png");
    Sprite grassSprite = Sprite(grassTexture);

    Texture dirtTexture = Texture();
    dirtTexture.loadFromFile("./Images/dirt_tile.png");
    Sprite dirtSprite = Sprite(dirtTexture);

    Texture backgroundTexture = Texture();
    backgroundTexture.loadFromFile("./Images/background.png");
    Sprite backgroundSprite = Sprite(backgroundTexture);

    Texture boxTexture = Texture();
    boxTexture.loadFromFile("./Images/box_tile.png");
    Sprite boxSprite = Sprite(boxTexture);

    // create backgrounds
    for (int i = 0; i < 20; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER }));
        components->renderers[newEntityID].texture = backgroundTexture;
        components->renderers[newEntityID].sprite = backgroundSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 0;
        pos = Vector2f(-512 + (512 * 2 * i), 800 - (64 * 8));
        components->transforms[newEntityID].position = pos;
    }

    // create initial flat space
    for (int i = 0; i < 35; i++)
    {
        newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
        components->renderers[newEntityID].texture = grassTexture;
        components->renderers[newEntityID].sprite = grassSprite;
        components->renderers[newEntityID].isFlipped = false;
        components->renderers[newEntityID].renderingOrder = 1;
        pos = Vector2f(0 + (64 * i), 800);
        components->transforms[newEntityID].position = pos;
        components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
        components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
        components->physicsBodies[newEntityID].bounds = Rect<float>(grassSprite.getGlobalBounds());
        components->physicsBodies[newEntityID].hasGravity = true;
        components->physicsBodies[newEntityID].isStatic = true;
        components->physicsBodies[newEntityID].isOnGround = false;

        // create dirt under the grass
        for (int x = 1; x <= 10; x++)
        {
            newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
            components->renderers[newEntityID].texture = dirtTexture;
            components->renderers[newEntityID].sprite = dirtSprite;
            components->renderers[newEntityID].isFlipped = false;
            components->renderers[newEntityID].renderingOrder = 1;
            Vector2f dirtPos = pos + Vector2f(0, 64 * x);
            components->transforms[newEntityID].position = dirtPos;
            components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
            components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
            components->physicsBodies[newEntityID].bounds = Rect<float>(dirtSprite.getGlobalBounds());
            components->physicsBodies[newEntityID].hasGravity = true;
            components->physicsBodies[newEntityID].isStatic = true;
            components->physicsBodies[newEntityID].isOnGround = false;
        }
    }

    // create box to fall
    newEntityID = ecs.AddEntity(ComponentsMask({ ComponentType::ENTITY_TRANSFORM, ComponentType::RENDERER, ComponentType::PHYSICS_BODY }));
    components->renderers[newEntityID].texture = boxTexture;
    components->renderers[newEntityID].sprite = boxSprite;
    components->renderers[newEntityID].isFlipped = false;
    components->renderers[newEntityID].renderingOrder = 1;
    pos = Vector2f(1000, 300);
    components->transforms[newEntityID].position = pos;
    //components->physicsBodies[newEntityID].velocity = Vector2f(500, 0);
    components->physicsBodies[newEntityID].gravityAccel = Vector2f(0, GRAV);
    components->physicsBodies[newEntityID].bounds = Rect<float>(boxSprite.getGlobalBounds());
    components->physicsBodies[newEntityID].hasGravity = true;
    components->physicsBodies[newEntityID].isStatic = false;
    components->physicsBodies[newEntityID].isOnGround = false;
    

    ecs.GameLoop();
}

int main()
{
    Components* components = ecs.GetComponents();
    int newEntityID;
    Vector2f pos;

    // scenes
    //Benchmark();
    //Game();
    TechDemo();
    //BoxDrop();

    return 0;
}