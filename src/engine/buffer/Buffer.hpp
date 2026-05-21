#pragma once
#include <vector>

namespace engine {
class Buffer {
private:
  unsigned int vao, vbo, ibo;

public:
  Buffer(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
  ~Buffer();

  void configure(const std::vector<unsigned int>& config);
  void bind(bool b = true) const;
};
} // namespace engine
