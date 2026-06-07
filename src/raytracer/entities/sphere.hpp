#pragma once
#include "hittable.hpp"

class Sphere : public Hittable {
private:
  glm::vec3 center;
  float radius;

public:
  Sphere(const glm::vec3 &center, float radius);

  virtual HitResult hit(const Ray &r, const Interval& ray_t) const override;
};
