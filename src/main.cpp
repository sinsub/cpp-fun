#include "main.h"
#include "BouncingBalls.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <stdio.h>
#include <chrono>

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

int main()
{
    BouncingBalls bb(5000);
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    auto window = sf::RenderWindow(sf::VideoMode({WIDTH, HEIGHT}),
                                   "SFML For Fun", STYLE,
                                   sf::State::Windowed, settings);
    window.setFramerateLimit(144);

    using namespace std::chrono;
    duration<float> delta_time(0);
    steady_clock::time_point last_time = steady_clock::now();

    while (window.isOpen())
    {
        steady_clock::time_point current_time = steady_clock::now();
        delta_time = duration_cast<duration<double>>(current_time - last_time);
        last_time = current_time;

        handle_events(window);
        window.clear();
        bb.update(delta_time.count());
        bb.draw(window);
        window.display();
    }
}

