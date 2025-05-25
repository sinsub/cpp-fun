// Copyright 2025 Subodh Singh

#include <iostream>
#include <memory>

#include "uif/context.h"
#include "uif/layout.h"
#include "uif/scene.h"

struct MyScene : public uif::Scene {
  explicit MyScene(int id) : uif::Scene(), id_(id) {
    std::cout << "MyScene(" << id << ")" << std::endl;
  }

  void OnCreate() override { std::cout << "MyScene(" << id_ << ").on_create" << std::endl; }

  void Render(uif::Context *context, uif::Layout *layout) override {
    sf::Color background;
    sf::Color primary;
    if (id_ % 2 == 0) {
      background = sf::Color::Black;
      primary = sf::Color::White;
    } else {
      background = sf::Color::White;
      primary = sf::Color::Black;
    }
    for (int i = 0; i < 3; i++) {
      float x = (i + 1) * 50 + i * 100;
      uif::Rect rect{};
      rect.x = x;
      rect.y = 100;
      rect.width = 100;
      rect.height = 100;
      rect.color = clicked_[i] ? sf::Color::Blue : primary;
      rect.on_hover = [i](uif::Rect *rect) {
        rect->border_thickness = 5;
        rect->border_color = sf::Color::Red;
      };
      rect.on_left_click = [i, this](uif::Rect *rect) {
        std::cout << "on_left_click(" << i << ")" << std::endl;
        this->clicked_[i] = !this->clicked_[i];
      };
      layout->AddRect(rect);
    }
    context->window->clear(background);
  }

  void OnDestory() override { std::cout << "MyScene(" << id_ << ").on_destroy" << std::endl; }

  ~MyScene() { std::cout << "~MyScene(" << id_ << ")" << std::endl; }

 private:
  int id_;
  int count_ = 0;
  bool clicked_[3] = {false, false, false};
};

int main() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;
  uif::Context context(std::make_unique<sf::RenderWindow>(sf::VideoMode({800, 600}),
                                                          "Test UI Framework", sf::Style::Default,
                                                          sf::State::Windowed, settings));
  context.SetScene(std::make_unique<MyScene>(0));
  context.Run();
}
