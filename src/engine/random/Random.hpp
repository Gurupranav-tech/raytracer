#pragma once

#include <cstdint>
#include <random>

namespace engine {
class Random {
private:
  static std::random_device rd;
  static std::mt19937 generator;
  static std::uniform_int_distribution<uint32_t> dist;
  static std::uniform_real_distribution<float> float_dist;

public:
  Random() = delete;

  static uint32_t random_uint32_t() noexcept;
  static float random_float() noexcept;
  static float random_float(float tmin, float tmax) noexcept;
};
} // namespace engine
