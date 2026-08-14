#pragma once
#include <math.h>

inline float linear_to_gamma(float component) {
  if (component > 0)
    return std::sqrt(component);
  return 0.0f;
}
