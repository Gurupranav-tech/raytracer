#include "Camera.hpp"

Camera::Camera(const glm::vec3 &camera_origin, float focal_length,
               uint32_t width, uint32_t height)
    : camera_center(camera_origin), focal_length(focal_length) {
  init(width, height);
}

Camera::Camera() : camera_center{0.0f, 0.0f, 0.0f}, focal_length{1.0f} {}

Ray Camera::get_ray(uint32_t i, uint32_t j) const noexcept {
  auto pixel_center = pixel00 + (float(i) * delta_u) + (float(j) * delta_v);
  auto ray_direction = pixel_center - camera_center;
  Ray ray(camera_center, ray_direction);

  return ray;
}

void Camera::zoom(float zoom, uint32_t width, uint32_t height) {
  focal_length += zoom / 10;
  init(width, height);
}

void Camera::change_center(glm::vec3 dc, uint32_t width, uint32_t height) {
  camera_center += dc;
  init(width, height);
}

void Camera::init(uint32_t width, uint32_t height) noexcept {
  float aspect_ratio = float(width) / height;

  float viewport_height = 2.0f;
  float viewport_width = viewport_height * aspect_ratio;

  viewport_u = {viewport_width, 0, 0};
  viewport_v = {0, -viewport_height, 0};

  delta_u = viewport_u / (float)width;
  delta_v = viewport_v / (float)height;

  auto viewport_upper_left = camera_center - glm::vec3(0, 0, focal_length) -
                             viewport_u / 2.0f - viewport_v / 2.0f;
  pixel00 = viewport_upper_left + 0.5f * (delta_u + delta_v);
}
