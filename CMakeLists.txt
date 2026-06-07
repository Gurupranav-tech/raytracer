cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(raytracer)

find_package(OpenGL REQUIRED)

find_package(OpenMP REQUIRED)

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

target_link_libraries(raytracer PUBLIC glfw imgui OpenGL::GL)

target_link_libraries(raytracer PRIVATE OpenMP::OpenMP_CXX)
