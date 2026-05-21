#pragma once

#include <chrono>

namespace engine {
class Timer {
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
  Timer() { start = std::chrono::high_resolution_clock::now(); }

  float elasped_time() {
    return std::chrono::duration<float>(
               std::chrono::high_resolution_clock::now() - start)
               .count() *
           1000;
  }
};
} // namespace engine
