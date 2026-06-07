#include "App.hpp"
#include <cstring>
#include <engine/random/Random.hpp>
#include <raytracer/entities/sphere.hpp>

App::App() : camera{Camera{}}, renderer{camera, world} {
  world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
  world.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));
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
