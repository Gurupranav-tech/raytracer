#pragma once
#include <math.h>
#include <glm/glm.hpp>

inline float linear_to_gamma(float component) {
  if (component > 0)
    return std::sqrt(component);
  return 0.0f;
}

inline bool vec_nearzero(const glm::vec3& vec) {
  if (std::fabs(vec.x) < 1e-4 && std::fabs(vec.y) < 1e-4 && std::fabs(vec.z) < 1e-4)
    return true;

  return false;
}
