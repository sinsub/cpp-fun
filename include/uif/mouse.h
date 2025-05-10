// Copyright 2025 Subodh Singh

#ifndef INCLUDE_UIF_MOUSE_H_
#define INCLUDE_UIF_MOUSE_H_

namespace uif {

// Keeps track of button state. The idea here is this can be
// queried for `down` and `up` which are per frame query, as well as
// `is_click`, `is_double_click`, which is a multi-frame query.
class MouseButtonState {
 public:
  void frame_reset();
  void record_down(int x, int y);
  void record_up(int x, int y);

  // queries
  bool down();
  bool up();

 private:
  bool down_ = false;
  bool up_ = false;
};

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
  MouseButtonState left, right;

  void init(int x, int y);
  void frame_reset();
  bool on_rect(float x, float y, float width, float height);
};

}  // namespace uif

#endif  // INCLUDE_UIF_MOUSE_H_
