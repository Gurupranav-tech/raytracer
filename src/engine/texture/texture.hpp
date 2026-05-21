#pragma once
#include <glad.h>

namespace engine {
class Texture {
private:
  int width, height, channels;
  unsigned int texture;
  unsigned int tex_unit;

public:
  Texture(const char *tex_file, unsigned int tex_unit = GL_TEXTURE0);
  Texture(int width, int height, int channels, unsigned char* data, unsigned int tex_unit = GL_TEXTURE0);

  void bind(bool t = true) const;

  ~Texture();

  inline int get_width() const noexcept { return width; }
  inline int get_height() const noexcept { return height; }
};
} // namespace engine
