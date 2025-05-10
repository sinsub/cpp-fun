// Copyright 2025 Subodh Singh

#include "uif/mouse.h"

#include <chrono>
#include <cstdlib>

namespace uif {

void MouseButtonState::FrameReset() { is_double_click_ = is_click_ = down_ = up_ = false; }

void MouseButtonState::RecordDown(int x, int y) {
  down_ = true;
  down_x_ = x;
  down_y_ = y;
  down_time_ = std::chrono::steady_clock::now();
}

// RecordUp seems to be invoked only after RecordDown
void MouseButtonState::RecordUp(int x, int y) {
  up_ = true;

  auto now = std::chrono::steady_clock::now();
  int dx = std::abs(x - down_x_);
  int dy = std::abs(y - down_y_);
  int dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - down_time_).count();
  bool dist_check = dx + dx <= kClickDistanceThreshold;
  bool time_check = dt <= kClickTimeThresholdMs;

  if (!dist_check || !time_check) {
    is_click_ = false;
    is_double_click_ = false;
    check_double_click_ = false;
    return;
  }

  is_click_ = true;

  if (!check_double_click_) {
    is_double_click_ = false;
    check_double_click_ = true;
    click_x_ = down_x_;
    click_y_ = down_y_;
    click_time_ = now;
    return;
  }

  dx = std::abs(x - click_x_);
  dy = std::abs(y - click_y_);
  dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - click_time_).count();

  dist_check = dx + dx <= kDoubleClickDistanceThreshold;
  time_check = dt <= kDoubleClickTimeThresholdMs;

  if (!dist_check || !time_check) {
    is_double_click_ = false;
    check_double_click_ = true;
    click_x_ = down_x_;
    click_y_ = down_y_;
    click_time_ = now;
    return;
  }

  is_double_click_ = true;
  check_double_click_ = false;
}

bool MouseButtonState::Down() { return down_; }

bool MouseButtonState::Up() { return up_; }

bool MouseButtonState::IsClick() { return is_click_; }

bool MouseButtonState::IsDoubleClick() { return is_double_click_; }

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
