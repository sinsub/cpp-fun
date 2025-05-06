#include <context.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace uif {

static void init(MouseState& mouse_state, sf::RenderWindow& window) {
    mouse_state.in_window = false;
    mouse_state.left_down = false;
    mouse_state.left_up = false;
    mouse_state.right_down = false;
    mouse_state.right_up = false;

    auto pos = sf::Mouse::getPosition(window);
    mouse_state.last_x = pos.x;
    mouse_state.last_y = pos.y;
}

static void reset_for_frame(MouseState& mouse_state) {
    mouse_state.left_down = false;
    mouse_state.left_up = false;
    mouse_state.right_down = false;
    mouse_state.right_up = false;
}

static bool mouse_on_rect(MouseState& ms, float x, float y, float width, float height) {
    if (!ms.in_window) return false;
    if (ms.last_x < x || ms.last_x > x + width) return false;
    if (ms.last_y < y || ms.last_y > y + height) return false;
    return true;
}

// BEGIN: public API

Context::Context(std::unique_ptr<sf::RenderWindow> window) : window(std::move(window)) {
    init(mouse_state, *(this->window));
}

void Context::run() {
    while (window->isOpen()) {
        process_events();
        process_sfml_events();
        render();
    }
}

void Context::set_scene(Scene* new_scene) {
    event_queue.push([this, new_scene]() {
        if (this->scene) {
            this->scene->on_destory();
            this->scene = nullptr;
        }
        this->scene = std::unique_ptr<Scene>(new_scene);
        if (this->scene) {
            this->scene->on_create();
        }
    });
}

// END: public API

// BEGIN: Render Loop

void Context::process_events() {
    while (!event_queue.empty()) {
        event_queue.front()();
        event_queue.pop();
    }
}

// done once per frame
void Context::process_sfml_events() {
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
    window->clear(sf::Color::Black);

    if (scene) {
        layout_manager.clear();
        scene->render(this, &layout_manager);
        for (auto rect : layout_manager.rects) {
            if (mouse_on_rect(mouse_state, rect.x, rect.y, rect.width, rect.height)) {
                rect.on_hover(&rect);
                if (mouse_state.left_down || mouse_state.right_down) {
                    rect.on_mouse_down(&rect);
                }
            }
            // TODO on_click
            sf::RectangleShape shape;
            shape.setSize({rect.width, rect.height});
            shape.setPosition({rect.x, rect.y});
            shape.setFillColor(rect.color);
            shape.setOutlineThickness(rect.border_thickness);
            shape.setOutlineColor(rect.border_color);
            window->draw(shape);
        }
    } else {
        default_render();
    }

    window->display();
}

void Context::default_render() {
    static std::vector<std::pair<float, float>> left_clicks{};
    static std::vector<std::pair<float, float>> right_clicks{};
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

// END: Render Loop

}  // namespace uif
