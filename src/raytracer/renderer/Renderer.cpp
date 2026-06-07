#include "Renderer.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <raytracer/entities/sphere.hpp>

constexpr uint32_t to_color(const glm::vec3 &col);

Renderer::Renderer() {
  world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
  world.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));
}

uint32_t Renderer::pixel(glm::vec2 coord) {
  auto ray = camera.get_ray(coord.x, coord.y);

  if (auto rec = world.hit(ray, Interval{0, INFINITY}); rec.has_value()) {
    return to_color((0.5f * (rec->normal + glm::vec3(1, 1, 1))) * 255.0f);
  }

  auto direction = ray.get_direction();
  direction = direction / (float)direction.length();
  auto a = 0.5f * (direction.y + 1.0f);

  glm::vec3 col =
      (1.0f - a) * glm::vec3(1.0, 1.0, 1.0) + a * glm::vec3(0.5, 0.7, 1.0);
  return to_color(col * 255.0f);
}

void Renderer::render() {
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

constexpr uint32_t to_color(const glm::vec3 &col) {
  uint32_t r = col.r;
  uint32_t g = col.g;
  uint32_t b = col.b;

  return 0xff000000 | (b << 16) | (g << 8) | r;
}
