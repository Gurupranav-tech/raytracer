#pragma once
#include <glm/glm.hpp>
#include <optional>
#include <raytracer/math/ray.hpp>

struct HitRecord {
  glm::vec3 point;
  glm::vec3 normal;
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

  virtual HitResult hit(const Ray &r, float tmin, float tmax) const = 0;
};
