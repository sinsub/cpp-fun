// Copyright 2025 Subodh Singh

#ifndef INCLUDE_UIF_SCENE_H_
#define INCLUDE_UIF_SCENE_H_

namespace uif {

// just declaration
struct Context;
struct Layout;

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

#endif  // INCLUDE_UIF_SCENE_H_
