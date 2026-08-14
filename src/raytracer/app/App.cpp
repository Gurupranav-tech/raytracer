#include "App.hpp"
#include "raytracer/config.hpp"
#include "raytracer/entities/lambertian.hpp"
#include "raytracer/entities/metal.hpp"
#include <cstring>
#include <engine/random/Random.hpp>
#include <raytracer/entities/sphere.hpp>

App::App() : camera{Camera{}}, renderer{camera, world, SAMPLES_PER_PIXEL} {
  auto material_ground = std::make_shared<Lambertian>(glm::vec3(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<Lambertian>(glm::vec3(0.1, 0.2, 0.5));
  auto material_left = std::make_shared<Metal>(glm::vec3(0.8, 0.8, 0.8), 1.0);
  auto material_right = std::make_shared<Metal>(glm::vec3(0.8, 0.6, 0.2), 0.3);

  world.add(std::make_shared<Sphere>(glm::vec3(0.0, -100.5, -1.0), 100.0,
                                     material_ground));
  world.add(std::make_shared<Sphere>(glm::vec3(0.0, 0.0, -1.2), 0.5,
                                     material_center));
  world.add(
      std::make_shared<Sphere>(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(
      std::make_shared<Sphere>(glm::vec3(1.0, 0.0, -1.0), 0.5, material_right));
}

App::~App() {}

void App::render() { renderer.render(); }

void App::on_zoom(float zoom) {
  camera.zoom(zoom, viewport_width, viewport_height);
}

void App::on_center_change(glm::vec3 dc) {
  camera.change_center(dc, viewport_width, viewport_height);
}

void App::set_viewport(uint32_t viewport_width, uint32_t viewport_height) {
  this->viewport_height = viewport_height;
  this->viewport_width = viewport_width;
  renderer.on_resize(viewport_width, viewport_height);
}
