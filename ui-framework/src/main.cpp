#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <utility>
#include <vector>

// BEGIN: MOUSE

// struct for storing the mouse state for a window.
// - `in_window`: has the mouse entered the window.
// - `last_x`: last known x position of the mouse, check `in_window`
// - `last_y`: last known y position of the mouse, check `in_window`
// - `left_down`: did we receive a left mouse down event in this frame
// - `left_up`: did we receive a left mouse up event in this frame
// - `right_down`: did we receive a right mouse down event in this frame
// - `right_up`: did we receive a right mouse up event in this frame
struct MouseState {
    bool in_window;
    int last_x;
    int last_y;
    bool left_down;
    bool left_up;
    bool right_down;
    bool right_up;
};

// As of now this is a global state, but may change if multi-window
static MouseState g_mouse_state;

// First initalization
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

// This should be called before processing events of a frame
static void reset_for_frame(MouseState& mouse_state) {
    mouse_state.left_down = false;
    mouse_state.left_up = false;
    mouse_state.right_down = false;
    mouse_state.right_up = false;
}

// END: MOUSE

void process_events(sf::RenderWindow& window) {
    reset_for_frame(g_mouse_state);
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (event->is<sf::Event::MouseEntered>()) {
            g_mouse_state.in_window = true;
        } else if (event->is<sf::Event::MouseLeft>()) {
            g_mouse_state.in_window = false;
        } else if (const auto* mm = event->getIf<sf::Event::MouseMoved>()) {
            g_mouse_state.last_x = mm->position.x;
            g_mouse_state.last_y = mm->position.y;
        } else if (const auto* mbp = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mbp->button == sf::Mouse::Button::Left) {
                g_mouse_state.left_down = true;
            } else if (mbp->button == sf::Mouse::Button::Right) {
                g_mouse_state.right_down = true;
            }
        } else if (const auto* mbr = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mbr->button == sf::Mouse::Button::Left) {
                g_mouse_state.left_up = true;
            }else if (mbr->button == sf::Mouse::Button::Right) {
                g_mouse_state.right_up = true;
            }
        }
    }
}

void render(sf::RenderWindow& window) {
    static std::vector<std::pair<float, float>> left_clicks{};
    static std::vector<std::pair<float, float>> right_clicks{};
    window.clear(sf::Color::Black);
    float radius = 10.f;
    sf::CircleShape dot(radius);
    for (auto loc : left_clicks) {
        dot.setFillColor(sf::Color::Red);
        dot.setPosition({loc.first, loc.second});
        window.draw(dot);
    }
    for (auto loc : right_clicks) {
        dot.setFillColor(sf::Color::Black);
        dot.setPosition({loc.first, loc.second});
        window.draw(dot);
    }
    if (g_mouse_state.in_window) {
        float x = g_mouse_state.last_x - radius;
        float y = g_mouse_state.last_y - radius;
        dot.setFillColor(sf::Color::White);
        dot.setPosition({x, y});
        window.draw(dot);
        if (g_mouse_state.left_down) {
            left_clicks.push_back({x, y});
        } else if (g_mouse_state.right_down) {
            right_clicks.push_back({x, y}); 
        }
    }
}

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test UI Framework", sf::Style::Default,
                            sf::State::Windowed, settings);
    init(g_mouse_state, window);
    while (window.isOpen()) {
        process_events(window);
        render(window);
        window.display();
    }
}
