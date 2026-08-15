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

  static inline glm::vec3 random_in_unitdisc() {
    while (true) {
      auto vector = glm::vec3{engine::Random::random_float(),
                              engine::Random::random_float(), 0.0f};
      if (glm::length(vector) < 1.0f)
        return vector;
    }
  }

  static inline glm::vec3 reflect(const glm::vec3 &direction,
                                  const glm::vec3 &normal) {
    float along_component = glm::dot(direction, normal);
    return direction - 2 * along_component * normal;
  }

  static inline glm::vec3 refract(const glm::vec3 &dirn,
                                  const glm::vec3 &normal, float n) {
    auto theta = std::fmin(glm::dot(-dirn, normal), 1.0f);
    auto perp = n * (dirn + theta * normal);
    auto parallel =
        -(float)std::sqrt(std::fabs(1.0 - std::pow(glm::length(perp), 2))) *
        normal;
    return perp + parallel;
  }
};
