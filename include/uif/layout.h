// Copyright 2025 Subodh Singh

#ifndef INCLUDE_UIF_LAYOUT_H_
#define INCLUDE_UIF_LAYOUT_H_

#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "functional"

namespace uif {

struct Rect {
  float x = 0, y = 0;
  float width = 0, height = 0;
  sf::Color color;
  sf::Color border_color;
  float border_thickness = 0;
  std::function<void(Rect*)> on_hover = [](Rect* rect) {};
  std::function<void(Rect*)> on_left_down = [](Rect* rect) {};
  std::function<void(Rect*)> on_right_down = [](Rect* rect) {};
  std::function<void(Rect*)> on_left_up = [](Rect* rect) {};
  std::function<void(Rect*)> on_right_up = [](Rect* rect) {};
  std::function<void(Rect*)> on_left_click = [](Rect* rect) {};
  std::function<void(Rect*)> on_right_click = [](Rect* rect) {};
  std::function<void(Rect*)> on_double_click = [](Rect* rect) {};
};

// Limited interface for `Scene`
struct Layout {
  virtual ~Layout() = default;
  virtual void AddRect(Rect rect) = 0;
  virtual void Clear() = 0;
};

// Full implementation for `Context`
struct LayoutManager : public Layout {
  void AddRect(Rect rect) override;
  void Clear() override;

  std::vector<Rect> rects;
};

}  // namespace uif

#endif  // INCLUDE_UIF_LAYOUT_H_
