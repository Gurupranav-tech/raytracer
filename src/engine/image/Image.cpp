#include "Image.hpp"

#include <glad.h>
#include <stdexcept>
#include <utility>

namespace engine {

// ─── Helpers ─────────────────────────────────────────────────────────────────

static GLenum ImageFormatToGLInternalFormat(ImageFormat format) {
  switch (format) {
  case ImageFormat::RGBA:
    return GL_RGBA8;
  case ImageFormat::RGBA32F:
    return GL_RGBA32F;
  default:
    throw std::invalid_argument("Unknown ImageFormat");
  }
}

static GLenum ImageFormatToGLDataFormat(ImageFormat format) {
  switch (format) {
  case ImageFormat::RGBA:
  case ImageFormat::RGBA32F:
    return GL_RGBA;
  default:
    throw std::invalid_argument("Unknown ImageFormat");
  }
}

static GLenum ImageFormatToGLDataType(ImageFormat format) {
  switch (format) {
  case ImageFormat::RGBA:
    return GL_UNSIGNED_BYTE;
  case ImageFormat::RGBA32F:
    return GL_FLOAT;
  default:
    throw std::invalid_argument("Unknown ImageFormat");
  }
}

uint32_t Image::GetBytesPerPixel(ImageFormat format) {
  switch (format) {
  case ImageFormat::RGBA:
    return 4;
  case ImageFormat::RGBA32F:
    return 16;
  default:
    return 0;
  }
}

// ─── Lifetime ────────────────────────────────────────────────────────────────

Image::Image(uint32_t width, uint32_t height, ImageFormat format,
             const void *data)
    : m_width(width), m_height(height), m_format(format) {
  AllocateMemory();
  if (data)
    SetData(data);
}

Image::~Image() { Release(); }

Image::Image(Image &&other) noexcept
    : m_width(other.m_width), m_height(other.m_height),
      m_format(other.m_format), m_rendererID(other.m_rendererID) {
  other.m_rendererID = 0;
  other.m_width = 0;
  other.m_height = 0;
}

Image &Image::operator=(Image &&other) noexcept {
  if (this != &other) {
    Release();
    m_width = other.m_width;
    m_height = other.m_height;
    m_format = other.m_format;
    m_rendererID = other.m_rendererID;
    other.m_rendererID = 0;
    other.m_width = 0;
    other.m_height = 0;
  }
  return *this;
}

// ─── Public API ──────────────────────────────────────────────────────────────

void Image::SetData(const void *data) {
  glBindTexture(GL_TEXTURE_2D, m_rendererID);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, static_cast<GLsizei>(m_width),
                  static_cast<GLsizei>(m_height),
                  ImageFormatToGLDataFormat(m_format),
                  ImageFormatToGLDataType(m_format), data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::Resize(uint32_t width, uint32_t height) {
  if (m_width == width && m_height == height)
    return;

  m_width = width;
  m_height = height;

  Release();
  AllocateMemory();
}

// ─── Private ─────────────────────────────────────────────────────────────────

void Image::AllocateMemory() {
  glGenTextures(1, &m_rendererID);
  glBindTexture(GL_TEXTURE_2D, m_rendererID);

  glTexImage2D(GL_TEXTURE_2D, 0,
               static_cast<GLint>(ImageFormatToGLInternalFormat(m_format)),
               static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height), 0,
               ImageFormatToGLDataFormat(m_format),
               ImageFormatToGLDataType(m_format),
               nullptr // no data yet — SetData() fills it
  );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::Release() {
  if (m_rendererID) {
    glDeleteTextures(1, &m_rendererID);
    m_rendererID = 0;
  }
}

} // namespace engine
