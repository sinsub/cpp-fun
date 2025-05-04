#include <context.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    uif::Context context(std::make_shared<sf::RenderWindow>(sf::VideoMode({800, 600}),
                                                            "Test UI Framework", sf::Style::Default,
                                                            sf::State::Windowed, settings));
    while (context.window->isOpen()) {
        context.process_events();
        context.render();
        context.window->display();
    }
}
