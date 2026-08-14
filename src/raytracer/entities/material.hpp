#pragma once
#include "hittable.hpp"
#include "raytracer/math/ray.hpp"
#include <optional>
#include <tuple>

using ScatterRecord = std::tuple<Ray, glm::vec3>;
using ScatterResult = std::optional<ScatterRecord>;

class Material {
public:
  virtual ~Material() = default;

  virtual ScatterResult scatter(const Ray &ray_in, const HitRecord &rec) {
    return std::nullopt;
  }
};
