#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <raytracer/math/interval.hpp>
#include <raytracer/math/ray.hpp>
#include <memory>

class Material;

struct HitRecord {
  glm::vec3 point;
  glm::vec3 normal;
  std::shared_ptr<Material> mat;
  float t;
  bool front_face;

  void set_face_normal(const Ray &r, const glm::vec3 &outward_normal) {
    front_face = glm::dot(outward_normal, r.get_direction()) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

using HitResult = std::optional<HitRecord>;

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual HitResult hit(const Ray &r, const Interval& ray_t) const = 0;
};
