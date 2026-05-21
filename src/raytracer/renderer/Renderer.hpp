#pragma once
#include <engine/image/Image.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <raytracer/camera/Camera.hpp>

class Renderer {
public:
  Renderer() = default;

  void render();
  void on_resize(uint32_t width, uint32_t height);

  inline const std::shared_ptr<engine::Image> &get_image() const noexcept {
    return image;
  }

private:
  std::shared_ptr<engine::Image> image;
  uint32_t *image_data = nullptr;
  Camera camera;

  uint32_t pixel(glm::vec2 coord);
};
