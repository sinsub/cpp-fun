#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

bool inWindow = false;

void processEvents(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (event->is<sf::Event::MouseEntered>()) {
            inWindow = true;
        } else if (event->is<sf::Event::MouseLeft>()) {
            inWindow = false;
        }
    }
}

void render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    if (inWindow) {
        auto pos = sf::Mouse::getPosition(window);
        float radius = 10.f;
        float x = pos.x - radius;
        float y = pos.y - radius;
        sf::CircleShape dot(radius);
        dot.setFillColor(sf::Color::White);
        dot.setPosition({x, y});
        window.draw(dot);
    }
}

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test UI Framework", sf::Style::Default,
                            sf::State::Windowed, settings);
    while (window.isOpen()) {
        processEvents(window);
        render(window);
        window.display();
    }
}
