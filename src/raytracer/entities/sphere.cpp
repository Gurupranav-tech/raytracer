#include "sphere.hpp"

Sphere::Sphere(const glm::vec3 &center, float radius,
               std::shared_ptr<Material> mat)
    : center{center}, radius{radius}, mat{mat} {}

HitResult Sphere::hit(const Ray &r, const Interval &ray_t) const {
  auto oc = center - r.get_origin();
  auto a = glm::dot(r.get_direction(), r.get_direction());
  auto h = glm::dot(oc, r.get_direction());
  auto c = glm::dot(oc, oc) - radius * radius;

  auto discriminant = h * h - a * c;
  if (discriminant < 0)
    return std::nullopt;

  auto sqrtd = std::sqrt(discriminant);

  auto root = (h - sqrtd) / a;
  if (!ray_t.surrounds(root)) {
    root = (h + sqrtd) / a;
    if (!ray_t.surrounds(root))
      return std::nullopt;
  }

  HitRecord record = {
      .point = r.at(root),
      .mat = mat,
      .t = root,
  };
  auto outward_normal = (r.at(root) - center) / radius;
  record.set_face_normal(r, outward_normal);

  return record;
}
