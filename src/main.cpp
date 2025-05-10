// Copyright 2025 Subodh Singh

#include <iostream>
#include <memory>

#include "uif/context.h"
#include "uif/layout.h"

struct MyScene : public uif::Scene {
  explicit MyScene(int id) : uif::Scene(), id_(id) {
    std::cout << "MyScene(" << id << ")" << std::endl;
  }

  void OnCreate() override {
    std::cout << "MyScene(" << id_ << ").on_create" << std::endl;
  }

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
      layout->AddRect({.x = x,
                       .y = 100,
                       .width = 100,
                       .height = 100,
                       .color = clicked_[i] ? sf::Color::Blue : primary,
                       .on_hover =
                           [](uif::Rect *rect) {
                             rect->border_thickness = 5;
                             rect->border_color = sf::Color::Red;
                           },
                       .on_mouse_down =
                           [i, this](uif::Rect *rect) {
                             this->clicked_[i] = !this->clicked_[i];
                           }});
    }
    context->window->clear(background);
    if (++count_ == 10000) {
      if (id_ < 2) {
        context->SetScene(std::make_unique<MyScene>(id_ + 1));
      } else {
        context->SetScene(nullptr);
      }
    }
  }

  void OnDestory() override {
    std::cout << "MyScene(" << id_ << ").on_destroy" << std::endl;
  }

  ~MyScene() { std::cout << "~MyScene(" << id_ << ")" << std::endl; }

 private:
  int id_;
  int count_ = 0;
  bool clicked_[3] = {false, false, false};
};

int main() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;
  uif::Context context(std::make_unique<sf::RenderWindow>(
      sf::VideoMode({800, 600}), "Test UI Framework", sf::Style::Default,
      sf::State::Windowed, settings));
  context.SetScene(std::make_unique<MyScene>(0));
  context.Run();
}
