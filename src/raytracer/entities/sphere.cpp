#include "sphere.hpp"

Sphere::Sphere(const glm::vec3 &center, float radius)
    : center{center}, radius{radius} {}

HitResult Sphere::hit(const Ray &r, float tmin, float tmax) const {
  auto oc = center - r.get_origin();
  auto a = glm::dot(r.get_direction(), r.get_direction());
  auto h = glm::dot(oc, r.get_direction());
  auto c = glm::dot(oc, oc) - radius * radius;

  auto discriminant = h * h - a * c;
  if (discriminant < 0)
    return std::nullopt;

  auto sqrtd = std::sqrt(discriminant);

  auto root = (h - sqrtd) / a;
  if (root <= tmin || tmax <= root) {
    root = (h + sqrtd) / a;
    if (root <= tmin || tmax <= root)
      return std::nullopt;
  }

  HitRecord record = {
      .point = r.at(root),
      .normal = (r.at(root) - center) / radius,
      .t = root,
  };

  return record;
}
