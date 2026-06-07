#include <engine/timer/Timer.hpp>
#include <engine/window/Window.hpp>
#include <glad.h>
#include <imgui.h>
#include <iostream>
#include <raytracer/app/App.hpp>
#include <raytracer/config.hpp>

int main() {
  engine::Window window(WIDTH, HEIGHT, "Raytracer");
  App app;

  const GLubyte *gpu = glGetString(GL_RENDERER);
  std::cout << "GPU being used: " << gpu << "\n";

  float last_render_time = 0.0f;
  window.run([&](float) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
    ImGui::Begin("Viewport");

    auto [x, y] = ImGui::GetContentRegionAvail();
    app.set_viewport(x, y);

    auto &image = app.get_image();
    if (image)
      ImGui::Image(image->GetDescriptorSet(),
                   {static_cast<float>(image->GetWidth()),
                    static_cast<float>(image->GetHeight())},
                   {1, 0}, {0, 1}); // flip Y for OpenGL);
                                    //
    if (ImGui::IsWindowHovered()) {
      auto io = ImGui::GetIO();
      if (ImGui::IsMouseDragging(ImGuiMouseButton_Right)) {
        ImVec2 delta = io.MouseDelta;

        constexpr float sensitivity = 0.005f;
      }

      float wheel = io.MouseWheel;
      if (wheel != 0.0f) {
        app.on_zoom(wheel);
      }
    }

    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::Begin("Settings");
    ImGui::Text("Last Render Time: %.3fms", last_render_time);
    ImGui::Text("FPS: %.3ffps", 1000 / last_render_time);
    // if (ImGui::Button("Render")) {
    engine::Timer timer;
    app.render();
    last_render_time = timer.elasped_time();
    // }
    ImGui::End();
  });
}
