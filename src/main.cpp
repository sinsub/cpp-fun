#include "main.h"

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "ecs/ECS.h"

static void handle_events(sf::RenderWindow &window);

struct Position2D {
    float y;
    float x;
};

int main()
{
    // test ECS
    ECS::EntityManager entityManager{};
    ECS::ComponentManager<Position2D> positionComponents{};
    ECS::Entity one = entityManager.createEntity();
    positionComponents.addComponent(one, {1.0, 2.0});
    Position2D *pos = positionComponents.getComponent(one);
    if (pos != nullptr) printf("Position of one: [%f, %f]\n", pos->y, pos->x);
    else printf("Something is wrong with the ECS\n");

    auto window = sf::RenderWindow(sf::VideoMode({WIDTH, HEIGHT}), "SFML For Fun", STYLE);
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        handle_events(window);
        window.clear();
        window.display();
    }
}

static void handle_events(sf::RenderWindow &window)
{

    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        if (event->is<sf::Event::Resized>())
        {
            auto size = window.getSize();
            printf("Resized: [%u, %u]\n", size.y, size.x);
        }
    }
}
