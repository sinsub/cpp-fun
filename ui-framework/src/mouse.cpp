#include <mouse.h>

namespace uif {

void MouseButtonState::frame_reset() {
    down_ = up_ = false;
}

void MouseButtonState::record_down(int x, int y) {
    down_ = true;
}

void MouseButtonState::record_up(int x, int y) {
    up_ = true;
}

bool MouseButtonState::down() {
    return down_;
}

bool MouseButtonState::up() {
    return up_;
}

void MouseState::init(int x, int y) {
    this->in_window = false;
    this->x = x;
    this->y = y;
    left.frame_reset();
    right.frame_reset();
}

void MouseState::frame_reset() {
    left.frame_reset();
    right.frame_reset();
}

bool MouseState::on_rect(float x, float y, float width, float height) {
    if (!this->in_window) return false;
    if (this->x < x || this->x > x + width) return false;
    if (this->y < y || this->y > y + height) return false;
    return true;
}

}  // namespace uif
