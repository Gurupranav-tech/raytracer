#pragma once
#include "hittable.hpp"
#include <memory>
#include "material.hpp"

class Sphere : public Hittable {
private:
  glm::vec3 center;
  float radius;
  std::shared_ptr<Material> mat;

public:
  Sphere(const glm::vec3 &center, float radius, std::shared_ptr<Material> mat);

  virtual HitResult hit(const Ray &r, const Interval& ray_t) const override;
};
