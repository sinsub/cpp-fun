#include "main.h"

#include <SFML/Graphics.hpp>
#include <stdio.h>

static void handle_events(sf::RenderWindow &window);

int main()
{
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
