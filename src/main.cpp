#include "main.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <stdio.h>
#include <random>
#include <vector>
#include "ecs/ECS.h"

static void handle_events(sf::RenderWindow &window);


const double LENGTH = 1.0;
const double RADIUS = 0.02;

static std::mt19937 gen(std::random_device{}());
static std::uniform_real_distribution<> posDis(RADIUS, LENGTH - RADIUS);
static std::uniform_real_distribution<> velDis(RADIUS, LENGTH - RADIUS);


static ECS::EntityManager entityManager{};
static ECS::ComponentManager<Position2D> positions;
static ECS::ComponentManager<Velocity2D> velocities;

static std::vector<ECS::Entity> discs;

static void init_entities(uint32_t count)
{
    while (count-- > 0)
    {
        ECS::Entity disc = entityManager.createEntity();
        discs.push_back(disc);
        positions.addComponent(disc, {posDis(gen), posDis(gen)});
        velocities.addComponent(disc, {velDis(gen), velDis(gen)});
    }
}

static void draw(sf::RenderWindow &window)
{
    float radius = RADIUS * WIDTH;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(0, 255, 255));
    for (auto entity: discs)
    {
        Position2D *pos = positions.getComponent(entity);
        float y = pos->y * HEIGHT;
        y -= radius;
        float x = pos->x * WIDTH;
        x -= radius;
        circle.setPosition({x, y});
        window.draw(circle);
    }
}

int main()
{
    init_entities(100);
    printf("Total Discs: %zu\n", discs.size());
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    auto window = sf::RenderWindow(sf::VideoMode({WIDTH, HEIGHT}), "SFML For Fun", STYLE, sf::State::Windowed, settings);
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        handle_events(window);
        window.clear();
        draw(window);
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
