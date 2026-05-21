#pragma once
#include <glm/glm.hpp>

class Ray {
private:
  glm::vec3 origin, direction;

public:
  Ray(const glm::vec3 &origin, const glm::vec3 &direction)
      : origin(origin), direction(direction) {}

  glm::vec3 at(float t) const noexcept { return origin + direction * t; }

  inline const glm::vec3 &get_origin() const noexcept { return origin; }
  inline const glm::vec3 &get_direction() const noexcept { return direction; }
};
