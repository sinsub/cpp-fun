#include <context.h>

#include <SFML/Graphics/CircleShape.hpp>

namespace uif {

static void init(MouseState& mouse_state, std::shared_ptr<sf::RenderWindow>& window) {
    mouse_state.in_window = false;
    mouse_state.left_down = false;
    mouse_state.left_up = false;
    mouse_state.right_down = false;
    mouse_state.right_up = false;

    auto pos = sf::Mouse::getPosition(*window);
    mouse_state.last_x = pos.x;
    mouse_state.last_y = pos.y;
}

static void reset_for_frame(MouseState& mouse_state) {
    mouse_state.left_down = false;
    mouse_state.left_up = false;
    mouse_state.right_down = false;
    mouse_state.right_up = false;
}

Context::Context(std::shared_ptr<sf::RenderWindow> window) {
    this->window = window;
    init(mouse_state, window);
}

// done once per frame
void Context::process_events() {
    reset_for_frame(mouse_state);
    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window->close();
        } else if (event->is<sf::Event::MouseEntered>()) {
            mouse_state.in_window = true;
        } else if (event->is<sf::Event::MouseLeft>()) {
            mouse_state.in_window = false;
        } else if (const auto* mm = event->getIf<sf::Event::MouseMoved>()) {
            mouse_state.last_x = mm->position.x;
            mouse_state.last_y = mm->position.y;
        } else if (const auto* mbp = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mbp->button == sf::Mouse::Button::Left) {
                mouse_state.left_down = true;
            } else if (mbp->button == sf::Mouse::Button::Right) {
                mouse_state.right_down = true;
            }
        } else if (const auto* mbr = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mbr->button == sf::Mouse::Button::Left) {
                mouse_state.left_up = true;
            } else if (mbr->button == sf::Mouse::Button::Right) {
                mouse_state.right_up = true;
            }
        }
    }
}

void Context::render() {
    static std::vector<std::pair<float, float>> left_clicks{};
    static std::vector<std::pair<float, float>> right_clicks{};
    window->clear(sf::Color::Black);
    float radius = 10.f;
    sf::CircleShape dot(radius);
    for (auto loc : left_clicks) {
        dot.setFillColor(sf::Color::Red);
        dot.setPosition({loc.first, loc.second});
        window->draw(dot);
    }
    for (auto loc : right_clicks) {
        dot.setFillColor(sf::Color::Black);
        dot.setPosition({loc.first, loc.second});
        window->draw(dot);
    }
    if (mouse_state.in_window) {
        float x = mouse_state.last_x - radius;
        float y = mouse_state.last_y - radius;
        dot.setFillColor(sf::Color::White);
        dot.setPosition({x, y});
        window->draw(dot);
        if (mouse_state.left_down) {
            left_clicks.push_back({x, y});
        } else if (mouse_state.right_down) {
            right_clicks.push_back({x, y});
        }
    }
}

}  // namespace uif
