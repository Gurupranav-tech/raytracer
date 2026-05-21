#include "texture.hpp"
#include "../stb/stb_image.h"
#include <glad.h>
#include <stdexcept>

namespace engine {
Texture::Texture(const char *tex_file, unsigned int tex_unit) {
  glGenTextures(1, &texture);
  this->tex_unit = tex_unit;
  unsigned char *data = stbi_load(tex_file, &width, &height, &channels, 0);

  if (!data)
    throw std::runtime_error("Cannot open the texture");

  glActiveTexture(tex_unit);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Texture::Texture(int width, int height, int channels, unsigned char *data,
                 unsigned int tex_unit)
    : width(width), height(height), channels(channels) {
  glGenTextures(1, &texture);
  this->tex_unit = tex_unit;

  glActiveTexture(tex_unit);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
               channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() { glDeleteTextures(1, &texture); }

void Texture::bind(bool t) const {
  glActiveTexture(tex_unit);
  if (!t)
    glBindTexture(GL_TEXTURE_2D, 0);
  else
    glBindTexture(GL_TEXTURE_2D, texture);
}
} // namespace engine
