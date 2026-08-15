#include "Renderer.hpp"
#include "raytracer/config.hpp"
#include "raytracer/math/interval.hpp"
#include "raytracer/math/utils.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <raytracer/entities/sphere.hpp>

uint32_t to_color(glm::vec3 &&col);

Renderer::Renderer(Camera &camera, HittableList &world,
                   uint32_t samples_per_pixel)
    : camera{camera}, world{world}, samples_per_pixel{samples_per_pixel} {}

glm::vec3 Renderer::pixel_color(const Ray &ray) {
  if (depth <= 0)
    return {0, 0, 0};

  depth--;
  if (auto rec =
          world.hit(ray, Interval{MIN_DISTANCE_BTN_CONSECUTIVE_HITS, INFINITY});
      rec.has_value()) {
    if (auto scatter_rec = rec->mat->scatter(ray, *rec);
        scatter_rec.has_value()) {
      auto &[scattered, attentuation] = *scatter_rec;
      return attentuation * pixel_color(scattered);
    }
    return {0, 0, 0};
  }

  auto direction = ray.get_direction();
  direction = direction / (float)glm::length(direction);
  auto a = 0.5f * (direction.y + 1.0f);

  glm::vec3 color =
      (1.0f - a) * glm::vec3(1.0, 1.0, 1.0) + a * glm::vec3(0.5, 0.7, 1.0);
  return color;
}

uint32_t Renderer::pixel(glm::vec2 coord) {
  glm::vec3 color{};

  for (uint32_t k = 0; k < samples_per_pixel; k++) {
    auto ray = camera.get_ray(coord.x, coord.y);
    depth = MAX_DEPTH;
    auto col = pixel_color(ray);

    color += col;
  }

  return to_color(color / (float)samples_per_pixel);
}

void Renderer::render() {
  for (uint32_t y = 0; y < image->GetHeight(); y++) {
    for (uint32_t x = 0; x < image->GetWidth(); x++) {
      image_data[x + y * image->GetWidth()] = pixel({x, y});
    }
    if (y % 100 == 0)
      printf("100 columns done, at: %i\n", y);
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

uint32_t to_color(glm::vec3 &&col) {
  const Interval intensity{0.0f, 0.9999f};

  col.r = linear_to_gamma(col.r);
  col.b = linear_to_gamma(col.b);
  col.g = linear_to_gamma(col.g);

  uint32_t r = intensity.clamp(col.r) * 255.0f;
  uint32_t g = intensity.clamp(col.g) * 255.0f;
  uint32_t b = intensity.clamp(col.b) * 255.0f;

  return 0xff000000 | (b << 16) | (g << 8) | r;
}
