// Copyright 2025 Subodh Singh

#ifndef INCLUDE_UIF_MOUSE_H_
#define INCLUDE_UIF_MOUSE_H_

/**
 * DETECTING CLICKS
 *  - In Retained Mode GUIs, clicks are detected per element by maintining per element state.
 *  - Since this is a Immedeate Mode GUI, GUI elements are not retained across fames.
 *  - So the only option is to define double click based on the position and timing of the events.
 */

namespace uif {

/**
 * Can be used to keep track of the state of a button.
 * For example, recording and query for down/up events.
 * More to be added: click, double click, drag
 */
class MouseButtonState {
 public:
  void FrameReset();
  void RecordDown(int x, int y);
  void RecordUp(int x, int y);

  // queries
  bool Down();
  bool Up();
  bool IsClick();

 private:
  bool down_ = false;
  bool up_ = false;

  bool is_click_ = false;
  int down_x_;
  int down_y_;

  static constexpr int kClickDistanceThreshold = 10;
};

/**
 * Can be used to keep track of the state of the mouse.
 * NOTE: `x` and `y` are relative to window and are accurate only if `in_window`
 * is true
 */
struct MouseState {
  bool in_window;
  int x;
  int y;
  MouseButtonState left_button, right_button;

  void Init(int x, int y);
  void FrameReset();
  bool OnRect(float x, float y, float width, float height);
};

}  // namespace uif

#endif  // INCLUDE_UIF_MOUSE_H_
