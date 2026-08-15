#pragma once
#include "engine/random/Random.hpp"
#include "material.hpp"

class Dielectirc : public Material {
private:
  float n;

public:
  Dielectirc(float n) : n{n} {}

  virtual ScatterResult scatter(const Ray &ray_in, const HitRecord &rec) {
    auto attentutation = glm::vec3{1, 1, 1};
    float ni = rec.front_face ? (1 / n) : n;

    auto direction =
        ray_in.get_direction() / glm::length(ray_in.get_direction());
    float cos_theta = std::fmin(glm::dot(-direction, rec.normal), 1.0f);
    float sin_theta = std::sqrt(1 - cos_theta * cos_theta);

    glm::vec3 final_direction;
    bool cannot_refract = ni * sin_theta > 1.0f;
    if (cannot_refract ||
        reflectance(cos_theta, ni) > engine::Random::random_float())
      final_direction = Ray::reflect(direction, rec.normal);
    else
      final_direction = Ray::refract(direction, rec.normal, ni);

    auto scattered = Ray{rec.point, final_direction};
    return std::make_tuple(scattered, attentutation);
  }

private:
  static float reflectance(float cosine, float n) {
    auto r0 = (1 - n) / (1 + n);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
  }
};
