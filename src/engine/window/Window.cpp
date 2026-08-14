#include "Window.hpp"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad.h>
#include <imgui.h>
#include <stdexcept>

GLFWwindow *g_Window = nullptr;

namespace engine {
Window::Window(unsigned int width, unsigned int height,
               const std::string &title)
    : width(width), height(height), title(title) {
  if (!glfwInit())
    throw std::runtime_error("Cannot initialize glfw");

  if (g_Window)
    return;

  g_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!g_Window)
    throw std::runtime_error("Cannot create window");
  glfwMakeContextCurrent(g_Window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  std::cout << glGetString(GL_VENDOR) << '\n';
  std::cout << glGetString(GL_RENDERER) << '\n';
  std::cout << glGetString(GL_VERSION) << '\n';
  std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, width, height);

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(g_Window, /*install_callbacks=*/true);
  ImGui_ImplOpenGL3_Init("#version 330 core");
}

Window::~Window() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  if (g_Window)
    glfwDestroyWindow(g_Window);
  glfwTerminate();
}

void Window::run(std::function<void(float)> fn) {
  while (!glfwWindowShouldClose(g_Window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Exit"))
          glfwSetWindowShouldClose(g_Window, true);
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});

    ImGuiWindowFlags dockFlags =
        ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_MenuBar;

    ImGui::Begin("##dockspace", nullptr, dockFlags);
    ImGui::PopStyleVar(3);

    ImGuiID dockId = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockId, {0.0f, 0.0f}, ImGuiDockNodeFlags_None);

    ImGui::End();

    fn((float)glfwGetTime());
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(g_Window);
  }
}
} // namespace engine
