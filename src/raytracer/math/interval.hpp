#pragma once
#include <math.h>

class Interval {
private:

public:
  float tmin, tmax;

public:
  Interval() : tmin{-INFINITY}, tmax{INFINITY} {}

  Interval(float tmin, float tmax) : tmin{tmin}, tmax{tmax} {}

  bool contains(float t) const noexcept { return tmin <= t && t <= tmax; }

  bool surrounds(float t) const noexcept { return tmin < t && t < tmax; }

  constexpr float length() const noexcept { return tmax - tmin; }

  static Interval universe() noexcept { return Interval{}; }

  static Interval empty() noexcept { return Interval{0, 0}; }
};
