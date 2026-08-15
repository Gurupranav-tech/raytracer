#include "App.hpp"
#include "raytracer/config.hpp"
#include "raytracer/entities/dielectric.hpp"
#include "raytracer/entities/lambertian.hpp"
#include "raytracer/entities/metal.hpp"
#include <cstring>
#include <engine/random/Random.hpp>
#include <raytracer/entities/sphere.hpp>

App::App()
    : camera{Camera{20, {13, 2, 3}, {0, 0, 0}, {0, 1, 0}, 0.6f, 3.4f}},
      renderer{camera, world, SAMPLES_PER_PIXEL} {
  auto ground_material = std::make_shared<Lambertian>(glm::vec3(0.5, 0.5, 0.5));
  world.add(
      std::make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = engine::Random::random_float();
      glm::vec3 center(a + 0.9 * engine::Random::random_float(), 0.2,
                       b + 0.9 * engine::Random::random_float());

      if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
        std::shared_ptr<Material> Sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = Ray::random() * Ray::random();
          Sphere_material = std::make_shared<Lambertian>(albedo);
          world.add(std::make_shared<Sphere>(center, 0.2, Sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = Ray::random(0.5, 1);
          auto fuzz = engine::Random::random_float(0, 0.5);
          Sphere_material = std::make_shared<Metal>(albedo, fuzz);
          world.add(std::make_shared<Sphere>(center, 0.2, Sphere_material));
        } else {
          // glass
          Sphere_material = std::make_shared<Dielectirc>(1.5);
          world.add(std::make_shared<Sphere>(center, 0.2, Sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<Dielectirc>(1.5);
  world.add(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<Lambertian>(glm::vec3(0.4, 0.2, 0.1));
  world.add(std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<Metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
  world.add(std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0, material3));
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
