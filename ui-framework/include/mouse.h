#ifndef UIF_MOUSE_H_
#define UIF_MOUSE_H_

namespace uif {

// struct for storing the mouse state for a window.
// - `in_window`: has the mouse entered the window.
// - `x`: last known x position of the mouse, check `in_window`
// - `y`: last known y position of the mouse, check `in_window`
// - `left_down`: did we receive a left mouse down event in this frame
// - `left_up`: did we receive a left mouse up event in this frame
// - `right_down`: did we receive a right mouse down event in this frame
// - `right_up`: did we receive a right mouse up event in this frame
struct MouseState {
    bool in_window;
    int x;
    int y;
    bool left_down;
    bool left_up;
    bool right_down;
    bool right_up;
};

void mouse_state_init(MouseState& mouse_state, int x, int y);
void reset_mouse_state_for_frame(MouseState& mouse_state);
bool mouse_on_rect(MouseState& ms, float x, float y, float width, float height);

}  // namespace uif

#endif
