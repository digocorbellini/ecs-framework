#include <SFML/Graphics.hpp>
#include "Components.h"
#include <cstdarg>
#include <iostream>

using namespace sf;

#define MAX_ENTITIES 30

// systems will operate on this struct of all components in the game
struct Components
{
    // Every entity has an entry in every list. Their component is
    // accessed by indexing using their entity id;
    EntityTransform transforms[MAX_ENTITIES];
    PhysicsBody physicsBodies[MAX_ENTITIES];
    Renderer renderers[MAX_ENTITIES];
    PlayerController playerControllers[MAX_ENTITIES];
} components;

struct Entity
{
    long componentMask;

    void AddComponent(ComponentType comp)
    {
        componentMask |= 1 << comp;
    }

    /*void AddComponent(ComponentType comp...)
    {
        va_list args;
        va_start(args, comp);

        while (args)
        {

        }

        va_end(args);
    }*/

    void RemoveComponent(ComponentType comp)
    {
        long mask = 1 << comp;
        mask = ~mask;
        componentMask &= mask;
    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}