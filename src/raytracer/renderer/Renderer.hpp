#pragma once
#include <engine/image/Image.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <raytracer/camera/Camera.hpp>
#include <raytracer/entities/hittable_list.hpp>

class Renderer {
public:
  Renderer(Camera &camera, HittableList &world, uint32_t samples_per_pixel = 2);

  void render();
  void on_resize(uint32_t width, uint32_t height);

  inline const std::shared_ptr<engine::Image> &get_image() const noexcept {
    return image;
  }

private:
  std::shared_ptr<engine::Image> image;
  uint32_t *image_data = nullptr;
  Camera &camera;
  HittableList &world;
  uint32_t samples_per_pixel;

  uint32_t pixel(glm::vec2 coord);
};
