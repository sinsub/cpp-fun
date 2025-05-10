// Copyright 2025 Subodh Singh

#include <iostream>
#include <memory>

#include "uif/context.h"
#include "uif/layout.h"

struct MyScene : public uif::Scene {
  explicit MyScene(int id) : uif::Scene(), id(id) {
    std::cout << "MyScene(" << id << ")" << std::endl;
  }

  void on_create() override {
    std::cout << "MyScene(" << id << ").on_create" << std::endl;
  }

  void render(uif::Context *context, uif::Layout *layout) override {
    sf::Color background;
    sf::Color primary;
    if (id % 2 == 0) {
      background = sf::Color::Black;
      primary = sf::Color::White;
    } else {
      background = sf::Color::White;
      primary = sf::Color::Black;
    }
    for (int i = 0; i < 3; i++) {
      float x = (i + 1) * 50 + i * 100;
      layout->add_rect({.x = x,
                        .y = 100,
                        .width = 100,
                        .height = 100,
                        .color = clicked[i] ? sf::Color::Blue : primary,
                        .on_hover =
                            [](uif::Rect *rect) {
                              rect->border_thickness = 5;
                              rect->border_color = sf::Color::Red;
                            },
                        .on_mouse_down =
                            [i, this](uif::Rect *rect) {
                              this->clicked[i] = !this->clicked[i];
                            }});
    }
    context->window->clear(background);
    if (++count == 10000) {
      if (id < 2) {
        context->set_scene(std::make_unique<MyScene>(id + 1));
      } else {
        context->set_scene(nullptr);
      }
    }
  }

  void on_destory() override {
    std::cout << "MyScene(" << id << ").on_destroy" << std::endl;
  }

  ~MyScene() { std::cout << "~MyScene(" << id << ")" << std::endl; }

 private:
  int id;
  int count = 0;
  bool clicked[3] = {false, false, false};
};

int main() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;
  uif::Context context(std::make_unique<sf::RenderWindow>(
      sf::VideoMode({800, 600}), "Test UI Framework", sf::Style::Default,
      sf::State::Windowed, settings));
  context.set_scene(std::make_unique<MyScene>(0));
  context.run();
}
