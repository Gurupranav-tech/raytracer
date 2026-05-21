cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(raytracer)


file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "./src/*.c" "./src/engine/**/*.c" "./src/engine/*.c" "./src/*.cpp" "./src/engine/**/*.cpp" "./src/engine/*.cpp" "./src/raytracer/**/*.cpp")

add_executable(raytracer ${SOURCE_FILES})

add_subdirectory("vendor/glfw")
add_subdirectory("vendor/glm")
add_subdirectory("vendor/imgui")

target_include_directories(raytracer PUBLIC "./src")
target_include_directories(raytracer PUBLIC "./vendor/glfw/include")
target_include_directories(raytracer PUBLIC "./vendor/glad")
target_include_directories(raytracer PUBLIC "./vendor/glm/")
target_include_directories(raytracer PUBLIC "./vendor/imgui")

target_link_libraries(raytracer PUBLIC glfw imgui)
