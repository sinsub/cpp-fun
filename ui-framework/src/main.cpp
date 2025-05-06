#include <context.h>
#include <layout.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>

struct MyScene : public uif::Scene {
    MyScene(int id) : uif::Scene(), id(id) { std::cout << "MyScene(" << id << ")" << std::endl; }

    void on_create() override { std::cout << "MyScene(" << id << ").on_create" << std::endl; }

    void render(uif::Context *context, uif::Layout *layout) override {
        if (id % 2 == 0) {
            context->window->clear(sf::Color::White);
            layout->add_rect({
                .x = 50,
                .y = 50,
                .width = 100,
                .height = 100,
                .color = sf::Color::Black
            });
            layout->add_rect({
                .x = 100,
                .y = 100,
                .width = 100,
                .height = 100,
                .color = sf::Color::Red
            });
        } else {
            context->window->clear(sf::Color::Black);
            layout->add_rect({
                .x = 50,
                .y = 50,
                .width = 100,
                .height = 100,
                .color = sf::Color::White
            });
            layout->add_rect({
                .x = 100,
                .y = 100,
                .width = 100,
                .height = 100,
                .color = sf::Color::Red
            });
        }
        if (++count == 5000) {
            if (id < 10) {
                context->set_scene(new MyScene(id + 1));
            } else {
                context->set_scene(nullptr);
            }
        }
    }

    void on_destory() override { std::cout << "MyScene(" << id << ").on_destroy" << std::endl; }

    ~MyScene() { std::cout << "~MyScene(" << id << ")" << std::endl; }

   private:
    int id;
    int count = 0;
};

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    uif::Context context(std::make_unique<sf::RenderWindow>(sf::VideoMode({800, 600}),
                                                            "Test UI Framework", sf::Style::Default,
                                                            sf::State::Windowed, settings));
    context.set_scene(new MyScene(0));
    context.run();
}
