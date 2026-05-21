#include "Random.hpp"

namespace engine {
std::random_device Random::rd;
std::mt19937 Random::generator(rd());
std::uniform_int_distribution<uint32_t> Random::dist(1, UINT32_MAX);

uint32_t Random::random_uint32_t() noexcept { return dist(generator); }
} // namespace engine
