// Copyright 2025 Subodh Singh

#include "uif/context.h"

#include <memory>
#include <utility>
#include <vector>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Mouse.hpp"
#include "uif/scene.h"

namespace uif {

// BEGIN: public API

Context::Context(std::unique_ptr<sf::RenderWindow> window) : window(std::move(window)) {
  auto pos = sf::Mouse::getPosition(*(this->window));
  mouse_state_.Init(pos.x, pos.y);
}

void Context::Run() {
  while (window->isOpen()) {
    ProcessEvents();
    ProcessSfmlEvents();
    Render();
  }
}

void Context::SetScene(std::unique_ptr<Scene> new_scene) {
  auto holder = std::make_shared<std::unique_ptr<Scene>>(std::move(new_scene));
  event_queue_.push([this, holder]() {
    if (this->scene_) {
      this->scene_->OnDestory();
      this->scene_ = nullptr;
    }
    this->scene_ = std::move(*holder);
    if (this->scene_) {
      this->scene_->OnCreate();
    }
  });
}

// END: public API

// BEGIN: Render Loop

void Context::ProcessEvents() {
  while (!event_queue_.empty()) {
    event_queue_.front()();
    event_queue_.pop();
  }
}

// done once per frame
void Context::ProcessSfmlEvents() {
  mouse_state_.FrameReset();
  // get the position all the time. This might be outside!
  auto pos = sf::Mouse::getPosition(*window);
  mouse_state_.x = pos.x;
  mouse_state_.y = pos.y;
  while (const std::optional event = window->pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window->close();
    } else if (const auto* re = event->getIf<sf::Event::Resized>()) {
      // update the view to the new size of the window
      float width = re->size.x;
      float height = re->size.y;
      sf::FloatRect visibleArea({0.0, 0.0}, {width, height});
      window->setView(sf::View(visibleArea));
    } else if (event->is<sf::Event::MouseEntered>()) {
      mouse_state_.in_window = true;
    } else if (event->is<sf::Event::MouseLeft>()) {
      mouse_state_.in_window = false;
    } else if (const auto* mbp = event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mbp->button == sf::Mouse::Button::Left) {
        mouse_state_.left_button.RecordDown(mouse_state_.x, mouse_state_.y);
      } else if (mbp->button == sf::Mouse::Button::Right) {
        mouse_state_.right_button.RecordDown(mouse_state_.x, mouse_state_.y);
      }
    } else if (const auto* mbr = event->getIf<sf::Event::MouseButtonReleased>()) {
      if (mbr->button == sf::Mouse::Button::Left) {
        mouse_state_.left_button.RecordUp(mouse_state_.x, mouse_state_.y);
      } else if (mbr->button == sf::Mouse::Button::Right) {
        mouse_state_.right_button.RecordUp(mouse_state_.x, mouse_state_.y);
      }
    }
  }
}

void Context::Render() {
  window->clear(sf::Color::Black);

  if (scene_) {
    layout_manager_.Clear();
    scene_->Render(this, &layout_manager_);
    for (auto rect : layout_manager_.rects) {
      // Mouse Events
      if (mouse_state_.OnRect(rect.x, rect.y, rect.width, rect.height)) {
        rect.on_hover(&rect);
        if (mouse_state_.left_button.Down()) {
          rect.on_left_down(&rect);
        }
        if (mouse_state_.right_button.Down()) {
          rect.on_right_down(&rect);
        }
        if (mouse_state_.left_button.Up()) {
          rect.on_left_up(&rect);
        }
        if (mouse_state_.right_button.Up()) {
          rect.on_right_up(&rect);
        }
        if (mouse_state_.left_button.IsClick()) {
          rect.on_left_click(&rect);
        }
        if (mouse_state_.right_button.IsClick()) {
          rect.on_right_click(&rect);
        }
        if (mouse_state_.left_button.IsDoubleClick()) {
          rect.on_double_click(&rect);
        }
      }

      sf::RectangleShape shape;
      shape.setSize({rect.width, rect.height});
      shape.setPosition({rect.x, rect.y});
      shape.setFillColor(rect.color);
      shape.setOutlineThickness(rect.border_thickness);
      shape.setOutlineColor(rect.border_color);
      window->draw(shape);
    }
  } else {
    DefaultRender();
  }

  window->display();
}

void Context::DefaultRender() {
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
  if (mouse_state_.in_window) {
    float x = mouse_state_.x - radius;
    float y = mouse_state_.y - radius;
    dot.setFillColor(sf::Color::White);
    dot.setPosition({x, y});
    window->draw(dot);
    if (mouse_state_.left_button.Down()) {
      left_clicks.push_back({x, y});
    } else if (mouse_state_.right_button.Down()) {
      right_clicks.push_back({x, y});
    }
  }
}

// END: Render Loop

}  // namespace uif
