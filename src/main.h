#pragma once

#include <SFML/Graphics.hpp>
#include <stdint.h>

const unsigned int HEIGHT = 600;
const unsigned int WIDTH  = 800;

const uint32_t STYLE = sf::Style::Titlebar | sf::Style::Close;

// A few balls, bouncing around. Each will have a random position
// and random velocity. They will be confined in a 1.0 x 1.0 rect
// and when they hit a wall they there will be elastic collission.

struct Position2D {
    double y;
    double x;
};

struct Velocity2D {
    double vy;
    double vx;
};


