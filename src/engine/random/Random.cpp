#include "Random.hpp"

namespace engine {
std::random_device Random::rd;
std::mt19937 Random::generator(rd());
std::uniform_int_distribution<uint32_t> Random::dist(1, UINT32_MAX);
std::uniform_real_distribution<float> Random::float_dist;

uint32_t Random::random_uint32_t() noexcept { return dist(generator); }

float Random::random_float() noexcept { return float_dist(generator); }

float Random::random_float(float tmin, float tmax) noexcept {
  return tmin + (tmax - tmin) * random_float();
}
} // namespace engine
