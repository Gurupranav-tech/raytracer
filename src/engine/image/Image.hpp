#pragma once

#include <cstdint>
#include <string>

namespace engine {

enum class ImageFormat {
  None = 0,
  RGBA,    // 4 bytes per pixel
  RGBA32F, // 16 bytes per pixel (HDR)
};

class Image {
public:
  Image(uint32_t width, uint32_t height, ImageFormat format,
        const void *data = nullptr);
  ~Image();

  // Non-copyable, movable
  Image(const Image &) = delete;
  Image &operator=(const Image &) = delete;
  Image(Image &&other) noexcept;
  Image &operator=(Image &&other) noexcept;

  // Upload CPU buffer → GPU. data must match the format and w×h dimensions.
  void SetData(const void *data);

  // Resize — releases and reallocates the GPU texture.
  void Resize(uint32_t width, uint32_t height);

  [[nodiscard]] uint32_t GetWidth() const { return m_width; }
  [[nodiscard]] uint32_t GetHeight() const { return m_height; }
  [[nodiscard]] ImageFormat GetFormat() const { return m_format; }
  [[nodiscard]] uint64_t GetDescriptorSet() const { return m_rendererID; }

  // Convenience: returns the ImTextureID cast, ready for ImGui::Image()
  [[nodiscard]] uint64_t GetImTextureID() const { return m_rendererID; }

  static uint32_t GetBytesPerPixel(ImageFormat format);

private:
  void AllocateMemory();
  void Release();

  uint32_t m_width = 0;
  uint32_t m_height = 0;
  ImageFormat m_format = ImageFormat::None;
  uint32_t m_rendererID = 0; // OpenGL texture handle
};

} // namespace engine
