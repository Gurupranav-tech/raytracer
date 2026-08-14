#pragma once
#include <glm/glm.hpp>
#include <string>

namespace engine {
class Shader {
private:
  unsigned int program;

public:
  Shader(const std::string &vertex, const std::string &fragment);
  ~Shader();

  void bind(bool b = true);
  void set_uniform(const char *name, int val);
  void set_uniform(const char *name, float val);
  void set_uniform(const char *name, glm::mat4 &mat);

private:
  static std::string read_file(const std::string &file);
};
} // namespace engine
