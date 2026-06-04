#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <raytracer/math/ray.hpp>

struct HitRecord {
  glm::vec3 point;
  glm::vec3 normal;
  float t;
};

using HitResult = std::optional<HitRecord>;

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual HitResult hit(const Ray &r, float tmin, float tmax) const = 0;
};
