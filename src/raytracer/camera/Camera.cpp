#include "Camera.hpp"
#include "engine/random/Random.hpp"
#include <cmath>
#include <math.h>

Camera::Camera() : camera_center{0.0f, 0.0f, 0.0f} {}

Camera::Camera(float fov, const glm::vec3 &look_from, const glm::vec3 &look_up,
               const glm::vec3 &vup, float defocus_angle, float focus_dist)
    : fov{fov}, look_from{look_from}, look_up{look_up}, vup{vup},
      defocs_angle{defocus_angle}, focus_dist{focus_dist} {}

Ray Camera::get_ray(uint32_t i, uint32_t j) const noexcept {
  auto offset = sample_square();
  auto pixel_center = pixel00 + (float(i + offset.x) * delta_u) +
                      (float(j + offset.y) * delta_v);
  auto ray_origin = (defocs_angle <= 0) ? camera_center : defocus_disk_sample();
  auto ray_direction = pixel_center - ray_origin;
  Ray ray(ray_origin, ray_direction);
  return ray;
}

void Camera::zoom(float zoom, uint32_t width, uint32_t height) {
  focus_dist += zoom / 10;
  init(width, height);
}

void Camera::change_center(glm::vec3 dc, uint32_t width, uint32_t height) {
  camera_center += dc;
  init(width, height);
}

void Camera::init(uint32_t width, uint32_t height) noexcept {
  float aspect_ratio = float(width) / height;

  camera_center = look_from;

  float viewport_height =
      std::tan(22.0f / 7 / 180 * fov / 2) * 2.0f * focus_dist;
  float viewport_width = viewport_height * aspect_ratio;
  printf("viewport_height: %f\n", viewport_height);

  auto w = (look_from - look_up) / glm::length(look_from - look_up);
  auto u = glm::cross(vup, w) / glm::length(glm::cross(vup, w));
  auto v = glm::cross(w, u);

  viewport_u = viewport_width * u;
  viewport_v = viewport_height * -v;

  delta_u = viewport_u / (float)width;
  delta_v = viewport_v / (float)height;

  auto viewport_upper_left =
      camera_center - (focus_dist * w) - viewport_u / 2.0f - viewport_v / 2.0f;
  pixel00 = viewport_upper_left + 0.5f * (delta_u + delta_v);

  auto defocus_radius =
      focus_dist * std::tan(22.0f / 7 / 180.0f * (defocs_angle / 2));
  defocus_disc_u = u * defocus_radius;
  defocus_disc_v = v * defocus_radius;
}

glm::vec3 Camera::defocus_disk_sample() const noexcept {
  auto p = Ray::random_in_unitdisc();
  return camera_center + (p[0] * defocus_disc_u) + (p[1] * defocus_disc_v);
}

glm::vec3 Camera::sample_square() const noexcept {
  return glm::vec3{engine::Random::random_float() - 0.5f,
                   engine::Random::random_float() - 0.5f, 0.0f};
}
