#ifndef UIF_CONTEXT_H_
#define UIF_CONTEXT_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
namespace uif {

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

// This is a context for a particular window. It 
struct Context {
    Context(std::unique_ptr<sf::RenderWindow> window);
    void process_events();
    void render();
    void run();

    // memers
    std::unique_ptr<sf::RenderWindow> window;
    MouseState mouse_state;
};

}  // namespace uif

#endif
