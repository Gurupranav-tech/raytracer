#pragma once

#include <glm/glm.hpp>
#include <raytracer/config.hpp>
#include <raytracer/math/ray.hpp>

class Camera {
private:
  glm::vec3 camera_center;

  glm::vec3 viewport_u, viewport_v, delta_u, delta_v, pixel00;
  float fov;

  glm::vec3 look_from, look_up, vup;
  float defocs_angle = 10.0f;
  float focus_dist = 3.4f;

  glm::vec3 defocus_disc_u, defocus_disc_v;

public:
  Camera();
  Camera(float fov, const glm::vec3 &look_from,
         const glm::vec3 &look_up, const glm::vec3 &vup,
         float defocs_angle = 10.0f, float focus_dist = 3.4f);

  void zoom(float zoom, uint32_t width, uint32_t height);

  void change_center(glm::vec3 dc, uint32_t width, uint32_t height);

  inline void on_screen_resize(uint32_t width, uint32_t height) noexcept {
    init(width, height);
  }

  Ray get_ray(uint32_t i, uint32_t j) const noexcept;

private:
  void init(uint32_t width, uint32_t height) noexcept;
  glm::vec3 sample_square() const noexcept;

  glm::vec3 defocus_disk_sample() const noexcept;
};
