#include "shader.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <cstdio>
#include <cstring>
#include <glad.h>
#include <iostream>
#include <stdexcept>

namespace engine {
Shader::Shader(const std::string &vertex, const std::string &fragment) {
  program = glCreateProgram();

  auto vertex_source = Shader::read_file(vertex);
  auto fragment_source = Shader::read_file(fragment);

  unsigned int v = glCreateShader(GL_VERTEX_SHADER);
  unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);

  auto vs = vertex_source.c_str();
  auto fs = fragment_source.c_str();

  glShaderSource(v, 1, &vs, nullptr);
  glCompileShader(v);
  int status;
  glGetShaderiv(v, GL_COMPILE_STATUS, &status);
  if (!status) {
    char buf[1024];
    glGetShaderInfoLog(v, 1024, nullptr, buf);

    std::cerr << buf << std::endl;
    throw std::runtime_error("Error compiling vertex shader");
  }

  glShaderSource(f, 1, &fs, nullptr);
  glCompileShader(f);
  glGetShaderiv(f, GL_COMPILE_STATUS, &status);
  if (!status) {
    char buf[1024];
    glGetShaderInfoLog(f, 1024, nullptr, buf);

    std::cerr << buf << std::endl;
    throw std::runtime_error("Error compiling fragment shader");
  }

  glAttachShader(program, v);
  glAttachShader(program, f);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (!status) {
    char buf[1024];
    glGetProgramInfoLog(program, 1024, nullptr, buf);

    std::cerr << buf << std::endl;
    throw std::runtime_error("Error linking program");
  }
}

void Shader::bind(bool b) {
  if (!b)
    glUseProgram(0);
  else
    glUseProgram(program);
}

void Shader::set_uniform(const char *name, int val) {
  bind();
  int location = glGetUniformLocation(program, name);
  glUniform1i(location, val);
}

void Shader::set_uniform(const char *name, glm::mat4 &mat) {
  bind();
  int location = glGetUniformLocation(program, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

Shader::~Shader() { glDeleteProgram(program); }

std::string Shader::read_file(const std::string &file) {
  FILE *f = fopen(file.c_str(), "r");
  if (f == nullptr)
    throw std::runtime_error("Cannot open the file");

  fseek(f, 0, SEEK_END);
  int size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *contents = new char[size + 1];
  memset(contents, 0, sizeof(char) * (size + 1));
  fread(contents, size, 1, f);

  return contents;
}
} // namespace engine
