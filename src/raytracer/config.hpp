#pragma once
#include <cstdint>

// Screen Sizes
constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr uint32_t WIDTH = 1920;
constexpr uint32_t HEIGHT = WIDTH / ASPECT_RATIO;

// Render Parameters
constexpr uint32_t RENDER_MAX_DEPTH = 8;
constexpr float MIN_DISTANCE_BTN_CONSECUTIVE_HITS = 0.01f;
