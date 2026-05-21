#pragma once
#include "engine/image/Image.hpp"
#include <raytracer/renderer/Renderer.hpp>
#include <cstdint>
#include <memory>

class App {
private:
  uint32_t viewport_width = 0;
  uint32_t viewport_height = 0;

  Renderer renderer;

public:
  App();
  ~App();

  void render();

  void set_viewport(uint32_t viewport_width, uint32_t viewport_height);

  inline const std::shared_ptr<engine::Image>& get_image() { return renderer.get_image();  }
};
