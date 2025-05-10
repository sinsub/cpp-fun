#include <context.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <memory>

namespace uif {

// BEGIN: public API

Context::Context(std::unique_ptr<sf::RenderWindow> window)
    : window(std::move(window)) {
  auto pos = sf::Mouse::getPosition(*(this->window));
  mouse_state.init(pos.x, pos.y);
}

void Context::run() {
  while (window->isOpen()) {
    process_events();
    process_sfml_events();
    render();
  }
}

void Context::set_scene(std::unique_ptr<Scene> new_scene) {
  auto holder = std::make_shared<std::unique_ptr<Scene>>(std::move(new_scene));
  event_queue.push([this, holder]() {
    if (this->scene) {
      this->scene->on_destory();
      this->scene = nullptr;
    }
    this->scene = std::move(*holder);
    if (this->scene) {
      this->scene->on_create();
    }
  });
}

// END: public API

// BEGIN: Render Loop

void Context::process_events() {
  while (!event_queue.empty()) {
    event_queue.front()();
    event_queue.pop();
  }
}

// done once per frame
void Context::process_sfml_events() {
  mouse_state.frame_reset();
  while (const std::optional event = window->pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window->close();
    } else if (event->is<sf::Event::MouseEntered>()) {
      mouse_state.in_window = true;
    } else if (event->is<sf::Event::MouseLeft>()) {
      mouse_state.in_window = false;
    } else if (const auto* mm = event->getIf<sf::Event::MouseMoved>()) {
      mouse_state.x = mm->position.x;
      mouse_state.y = mm->position.y;
    } else if (const auto* mbp =
                   event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mbp->button == sf::Mouse::Button::Left) {
        mouse_state.left.record_down(mouse_state.x, mouse_state.y);
      } else if (mbp->button == sf::Mouse::Button::Right) {
        mouse_state.right.record_down(mouse_state.x, mouse_state.y);
      }
    } else if (const auto* mbr =
                   event->getIf<sf::Event::MouseButtonReleased>()) {
      if (mbr->button == sf::Mouse::Button::Left) {
        mouse_state.left.record_up(mouse_state.x, mouse_state.y);
      } else if (mbr->button == sf::Mouse::Button::Right) {
        mouse_state.right.record_up(mouse_state.x, mouse_state.y);
      }
    }
  }
}

void Context::render() {
  window->clear(sf::Color::Black);

  if (scene) {
    layout_manager.clear();
    scene->render(this, &layout_manager);
    for (auto rect : layout_manager.rects) {
      if (mouse_state.on_rect(rect.x, rect.y, rect.width, rect.height)) {
        rect.on_hover(&rect);
        if (mouse_state.left.down()) {
          rect.on_mouse_down(&rect);
        }
      }
      // TODO on_click
      sf::RectangleShape shape;
      shape.setSize({rect.width, rect.height});
      shape.setPosition({rect.x, rect.y});
      shape.setFillColor(rect.color);
      shape.setOutlineThickness(rect.border_thickness);
      shape.setOutlineColor(rect.border_color);
      window->draw(shape);
    }
  } else {
    default_render();
  }

  window->display();
}

void Context::default_render() {
  static std::vector<std::pair<float, float>> left_clicks{};
  static std::vector<std::pair<float, float>> right_clicks{};
  float radius = 10.f;
  sf::CircleShape dot(radius);
  for (auto loc : left_clicks) {
    dot.setFillColor(sf::Color::Red);
    dot.setPosition({loc.first, loc.second});
    window->draw(dot);
  }
  for (auto loc : right_clicks) {
    dot.setFillColor(sf::Color::Black);
    dot.setPosition({loc.first, loc.second});
    window->draw(dot);
  }
  if (mouse_state.in_window) {
    float x = mouse_state.x - radius;
    float y = mouse_state.y - radius;
    dot.setFillColor(sf::Color::White);
    dot.setPosition({x, y});
    window->draw(dot);
    if (mouse_state.left.down()) {
      left_clicks.push_back({x, y});
    } else if (mouse_state.right.down()) {
      right_clicks.push_back({x, y});
    }
  }
}

// END: Render Loop

}  // namespace uif
