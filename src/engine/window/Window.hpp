#pragma once
#include <string>
#include <functional>

namespace engine {
class Window {
private:
  unsigned int width;
  unsigned int height;
  std::string title;

public:
  Window(unsigned int width, unsigned int height, const std::string& title);
  ~Window();

  void run(std::function<void(float)> fn);
  inline unsigned int get_width() const noexcept { return width; }
  inline unsigned int get_height() const noexcept { return height; }
};
} // namespace engine
