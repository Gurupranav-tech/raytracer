#pragma once
#include <math.h>

class Interval {
private:
public:
  float tmin, tmax;

public:
  Interval() : tmin{-INFINITY}, tmax{INFINITY} {}

  Interval(float tmin, float tmax) : tmin{tmin}, tmax{tmax} {}

  constexpr bool contains(float t) const noexcept {
    return tmin <= t && t <= tmax;
  }

  constexpr bool surrounds(float t) const noexcept {
    return tmin < t && t < tmax;
  }

  constexpr float clamp(float t) const noexcept {
    if (t < tmin)
      return tmin;
    if (t > tmax)
      return tmax;

    return t;
  }

  constexpr float length() const noexcept { return tmax - tmin; }

  static Interval universe() noexcept { return Interval{}; }

  static Interval empty() noexcept { return Interval{0, 0}; }
};
