#pragma once

#include "../interval/Interval.hpp"
#include "../vec3/Vec3.hpp"
#include <cmath>
#include <iostream>

using Color = Vec3;

inline double linear_to_gamma(double linear_component);

Color write_color(std::ostream& out , const Color& pixel_color);
