#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <vector>
#include "ecs/ECS.h"

// A few balls, bouncing around. Each will have a random position
// and random velocity. They will be confined in a 1.0 x 1.0 rect
// and when they hit a wall they there will be elastic collission.

const double LENGTH = 1.0;
const double RADIUS = 0.0025;

struct Position2D {
    double y;
    double x;
};

struct Velocity2D {
    double vy;
    double vx;
};

class BouncingBalls
{
public:
    BouncingBalls(uint32_t count);
    void update(double dt);
    void draw(sf::RenderWindow &window);
private:
    uint32_t count;
    std::vector<ECS::Entity> discs;
    ECS::EntityManager entityManager;
    ECS::ComponentManager<Position2D> positions;
    ECS::ComponentManager<Velocity2D> velocities;
};


