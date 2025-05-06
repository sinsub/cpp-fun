#ifndef UIF_LAYOUT_H_
#define UIF_LAYOUT_H_

#include <SFML/Graphics/Color.hpp>
#include <functional>
#include <vector>

// TODO: define a Color type

namespace uif {

// During render, first `on_hover` and `on_click` are evaluated.
// These might change the look of the Rect. So the final render
// is performed after evaluating these "modifers" (idk what to call them).
struct Rect {
    float x = 0, y = 0;
    float width = 0, height =  0;
    sf::Color color = sf::Color::White;
    std::function<void(Rect*)> on_click = [](Rect* rect) {};
    std::function<void(Rect*)> on_hover = [](Rect* rect) {};
};

// Limited interface for `Scene`
struct Layout {
    virtual ~Layout() = default;
    virtual void add_rect(Rect rect) = 0;
    virtual void clear() = 0;
};

// Full implementation for `Context`
struct LayoutManager : public Layout {
    void add_rect(Rect rect) override;
    void clear() override;

    std::vector<Rect> rects;
};

}  // namespace uif

#endif
