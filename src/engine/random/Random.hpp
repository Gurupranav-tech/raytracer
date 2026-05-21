#pragma once

#include <cstdint>
#include <random>

namespace engine {
class Random {
private:
  static std::random_device rd;
  static std::mt19937 generator;
  static std::uniform_int_distribution<uint32_t> dist;

public:
  Random() = delete;

  static uint32_t random_uint32_t() noexcept;
};
} // namespace engine
