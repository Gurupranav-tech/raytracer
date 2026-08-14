#pragma once
#include "engine/random/Random.hpp"
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

  static inline glm::vec3 random() {
    return {engine::Random::random_float(), engine::Random::random_float(),
            engine::Random::random_float()};
  }

  static inline glm::vec3 random(float tmin, float tmax) {
    return {engine::Random::random_float(tmin, tmax),
            engine::Random::random_float(tmin, tmax),
            engine::Random::random_float(tmin, tmax)};
  }

  static inline glm::vec3 random_unitvector() {
    while (true) {
      auto vector = random();
      float length = glm::length(vector);
      if (1e-60 < length && length <= 1)
        return vector / (float)sqrt(length);
    }
  }

  static inline glm::vec3 random_on_hemisphere(const glm::vec3 &normal) {
    auto vector = random_unitvector();
    if (glm::dot(vector, normal) >= 0.0f)
      return vector;
    else
      return -vector;
  }
};
