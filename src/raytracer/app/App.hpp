#pragma once
#include "engine/image/Image.hpp"
#include "raytracer/camera/Camera.hpp"
#include <cstdint>
#include <memory>
#include <raytracer/renderer/Renderer.hpp>

class App {
private:
  uint32_t viewport_width = 0;
  uint32_t viewport_height = 0;

  HittableList world;
  Camera camera;
  Renderer renderer;

public:
  App();
  ~App();

  void render();

  void set_viewport(uint32_t viewport_width, uint32_t viewport_height);

  void on_zoom(float zoom);

  inline const std::shared_ptr<engine::Image> &get_image() {
    return renderer.get_image();
  }
};
