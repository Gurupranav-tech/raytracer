#include "App.hpp"
#include <cstring>
#include <engine/random/Random.hpp>

App::App() {}

App::~App() {}

void App::render() {
  renderer.on_resize(viewport_width, viewport_height);
  renderer.render();
}

void App::set_viewport(uint32_t viewport_width, uint32_t viewport_height) {
  this->viewport_height = viewport_height;
  this->viewport_width = viewport_width;
}
