// Copyright 2025 Subodh Singh

#ifndef INCLUDE_UIF_CONTEXT_H_
#define INCLUDE_UIF_CONTEXT_H_

#include <functional>
#include <memory>
#include <queue>

#include "SFML/Graphics/RenderWindow.hpp"
#include "uif/layout.h"
#include "uif/mouse.h"

namespace uif {

// forward delarations for Context
struct Scene;

// Context for a particular window.
class Context {
 public:
  explicit Context(std::unique_ptr<sf::RenderWindow> window);

  // Start running the window. Returns after the window has been closed!
  void Run();

  // Set a particular scene, this is asynchronous.
  // Switch occurs at the start of the next frame.
  void SetScene(std::unique_ptr<Scene> scene);

 private:
  // The following three methods are interally called by `run`
  // in the exact sequence for each frame.

  // Processes events that were received by the context (`event_queue`)
  void ProcessEvents();

  // Processs events that were received by the `sf::RenderWindow`
  void ProcessSfmlEvents();

  // If there is a  `scene`, calls `scene->Render(this)`.
  // If there is no `scene`, calls `DefaultRender`
  void Render();

  void DefaultRender();

  // Data members
 public:
  // TODO(subodh): decide if this should be private
  std::unique_ptr<sf::RenderWindow> window;

 private:
  MouseState mouse_state_;
  std::unique_ptr<Scene> scene_;
  std::queue<std::function<void()>> event_queue_;
  LayoutManager layout_manager_;
};

struct Scene {
  virtual ~Scene() = default;

  // invoked once when the scene is set
  virtual void OnCreate() = 0;

  // invoked every frame to render the scene
  virtual void Render(Context *context, Layout *layout) = 0;

  // invoked once when this scene is replaced/removed
  virtual void OnDestory() = 0;
};

}  // namespace uif

#endif  // INCLUDE_UIF_CONTEXT_H_
