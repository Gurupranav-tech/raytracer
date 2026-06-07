#pragma once

#include <glm/glm.hpp>
#include <raytracer/config.hpp>
#include <raytracer/math/ray.hpp>

class Camera {
private:
  glm::vec3 camera_center;
  float focal_length = 0.0f;

  glm::vec3 viewport_u, viewport_v, delta_u, delta_v, pixel00;

public:
  Camera();
  Camera(const glm::vec3 &camera_center, float focal_length, uint32_t width,
         uint32_t height);

  void zoom(float zoom, uint32_t width, uint32_t height);

  inline void on_screen_resize(uint32_t width, uint32_t height) noexcept {
    init(width, height);
  }

  Ray get_ray(uint32_t i, uint32_t j) const noexcept;

private:
  void init(uint32_t width, uint32_t height) noexcept;
};
