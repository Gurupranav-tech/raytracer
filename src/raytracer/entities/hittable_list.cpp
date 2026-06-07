#include "hittable_list.hpp"

HittableList::HittableList(std::shared_ptr<Hittable> object) {
  add(std::move(object));
}

void HittableList::add(std::shared_ptr<Hittable> object) {
  objects.push_back(std::move(object));
}

void HittableList::clear() { objects.clear(); }

HitResult HittableList::hit(const Ray &r, const Interval& ray_t) const {
  float min_t = ray_t.tmax;
  HitResult result = std::nullopt;

  for (const auto &object : objects) {
    if (auto rec = object->hit(r, Interval(ray_t.tmin, min_t)); rec.has_value()) {
      min_t = rec->t;
      result = rec;
    }
  }

  return result;
}
