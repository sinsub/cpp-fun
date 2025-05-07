#include <mouse.h>

namespace uif {

void mouse_state_init(MouseState& mouse_state, int x, int y) {
    mouse_state.in_window = false;
    mouse_state.left_down = false;
    mouse_state.left_up = false;
    mouse_state.right_down = false;
    mouse_state.right_up = false;
    mouse_state.x = x;
    mouse_state.y = y;
}

void reset_mouse_state_for_frame(MouseState& mouse_state) {
    mouse_state.left_down = false;
    mouse_state.left_up = false;
    mouse_state.right_down = false;
    mouse_state.right_up = false;
}

bool mouse_on_rect(MouseState& ms, float x, float y, float width, float height) {
    if (!ms.in_window) return false;
    if (ms.x < x || ms.x > x + width) return false;
    if (ms.y < y || ms.y > y + height) return false;
    return true;
}

}  // namespace uif
