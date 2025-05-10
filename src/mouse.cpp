// Copyright 2025 Subodh Singh

#include "uif/mouse.h"

namespace uif {

void MouseButtonState::FrameReset() { down_ = up_ = false; }

void MouseButtonState::RecordDown(int x, int y) { down_ = true; }

void MouseButtonState::RecordUp(int x, int y) { up_ = true; }

bool MouseButtonState::Down() { return down_; }

bool MouseButtonState::Up() { return up_; }

void MouseState::Init(int x, int y) {
  this->in_window = false;
  this->x = x;
  this->y = y;
  left_button.FrameReset();
  right_button.FrameReset();
}

void MouseState::FrameReset() {
  left_button.FrameReset();
  right_button.FrameReset();
}

bool MouseState::OnRect(float x, float y, float width, float height) {
  if (!this->in_window) return false;
  if (this->x < x || this->x > x + width) return false;
  if (this->y < y || this->y > y + height) return false;
  return true;
}

}  // namespace uif
