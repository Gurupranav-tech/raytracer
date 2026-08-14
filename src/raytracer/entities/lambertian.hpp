#pragma once
#include "material.hpp"
#include "raytracer/math/utils.hpp"

class Lambertian : public Material {
private:
  glm::vec3 albedo;

public:
  Lambertian(const glm::vec3 &albedo) : albedo{albedo} {}

  virtual ScatterResult scatter(const Ray &ray_in,
                                const HitRecord &rec) override {
    auto direction = rec.normal + Ray::random_unitvector();
    if (vec_nearzero(direction))
      direction = rec.normal;

    auto scattered = Ray{rec.point, direction};

    return std::make_optional(std::make_tuple(scattered, albedo));
  }
};
