#include "Buffer.hpp"
#include "glad.h"
#include <algorithm>

namespace engine {
Buffer::Buffer(const std::vector<float> &vertices,
               const std::vector<unsigned int> &indices) {
  glGenVertexArrays(1, &vao);
  glGenBuffers(2, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               indices.data(), GL_STATIC_DRAW);
}

void Buffer::configure(const std::vector<unsigned int> &config) {
  unsigned int total{};
  std::for_each(config.begin(), config.end(), [&](auto x) { total += x; });

  unsigned int stride = 0;
  for (int i = 0; i < config.size(); i++) {
    glVertexAttribPointer(i, config[i], GL_FLOAT, GL_FALSE,
                          total * sizeof(float),
                          (void *)(stride * sizeof(float)));
    glEnableVertexAttribArray(i);
    stride += config[i];
  }
}

void Buffer::bind(bool b) const {
  if (!b) {
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  } else {
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  }
}

Buffer::~Buffer() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(2, &vbo);
}
} // namespace engine
