#pragma once
#include "material.hpp"

class Metal : public Material {
private:
  glm::vec3 albedo;
  float fuzz;

public:
  Metal(const glm::vec3 &albedo, float fuzz) : albedo{albedo}, fuzz{fuzz} {}

  virtual ScatterResult scatter(const Ray &ray_in,
                                const HitRecord &rec) override {
    auto direction = Ray::reflect(ray_in.get_direction(), rec.normal);
    direction = (direction / glm::length(direction)) + fuzz * Ray::random_unitvector();
    if (glm::dot(direction, rec.normal) <= 0)
      return std::nullopt;

    auto scattered = Ray{rec.point, direction};
    return std::make_optional(std::make_tuple(scattered, albedo));
  }
};
