#include "Renderer.hpp"
#include "raytracer/math/interval.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <raytracer/entities/sphere.hpp>

uint32_t to_color(const glm::vec3 &col);

Renderer::Renderer(Camera &camera, HittableList &world,
                   uint32_t samples_per_pixel)
    : camera{camera}, world{world}, samples_per_pixel{samples_per_pixel} {}

uint32_t Renderer::pixel(glm::vec2 coord) {
  glm::vec3 color{};

  for (uint32_t k = 0; k < samples_per_pixel; k++) {
    auto ray = camera.get_ray(coord.x, coord.y);
    if (auto rec = world.hit(ray, Interval{0, INFINITY}); rec.has_value()) {
      color += 0.5f * (rec->normal + glm::vec3(1, 1, 1));
      continue;
    }

    auto direction = ray.get_direction();
    direction = direction / (float)direction.length();
    auto a = 0.5f * (direction.y + 1.0f);

    glm::vec3 col =
        (1.0f - a) * glm::vec3(1.0, 1.0, 1.0) + a * glm::vec3(0.5, 0.7, 1.0);
    color += col;
  }

  return to_color(color / (float)samples_per_pixel);
}

void Renderer::render() {
#pragma omp parallel for schedule(dynamic)
  for (uint32_t y = 0; y < image->GetHeight(); y++) {
    for (uint32_t x = 0; x < image->GetWidth(); x++) {
      image_data[x + y * image->GetWidth()] = pixel({x, y});
    }
  }

  image->SetData(image_data);
}

void Renderer::on_resize(uint32_t width, uint32_t height) {
  if (image) {
    if (image->GetWidth() == width && image->GetHeight() == height)
      return;

    image->Resize(width, height);
  } else {
    image = std::make_shared<engine::Image>(width, height,
                                            engine::ImageFormat::RGBA);
  }

  delete[] image_data;
  image_data = new uint32_t[width * height];
  camera.on_screen_resize(width, height);
}

uint32_t to_color(const glm::vec3 &col) {
  const Interval intensity{0.0f, 0.9999f};

  uint32_t r = intensity.clamp(col.r) * 255.0f;
  uint32_t g = intensity.clamp(col.g) * 255.0f;
  uint32_t b = intensity.clamp(col.b) * 255.0f;

  return 0xff000000 | (b << 16) | (g << 8) | r;
}
