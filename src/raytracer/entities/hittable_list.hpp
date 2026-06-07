#pragma once

#include "hittable.hpp"
#include "raytracer/math/ray.hpp"
#include <memory>
#include <vector>

class HittableList : public Hittable {
private:
  std::vector<std::shared_ptr<Hittable>> objects;

public:
  HittableList() = default;
  HittableList(std::shared_ptr<Hittable> object);

  void clear();
  void add(std::shared_ptr<Hittable> object);

  HitResult hit(const Ray &r, const Interval& ray_t) const override;
};
