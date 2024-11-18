#include "Color.hpp"


double linear_to_gamma(double linear_component) {
    if(linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}


void write_color(std::ostream& out , const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const Interval intensity(0.000, 0.999);
    int ir = int(256 * intensity.clamp(r));
    int ig = int(256 * intensity.clamp(g));
    int ib = int(256 * intensity.clamp(b));

    out << ir << ' ' << ig << ' ' << ib << '\n';
}
