#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>

#include "Camera.hpp"
#include "../Utils.hpp"

void Camera::render(const Hittable& world) {
    initialise();

    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "Ray tracing");

    sf::Image i_image;
    i_image.create(image_width, image_height);

    /*std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";*/

    for(int j = 0; j < image_height; j++) {
        for(int i = 0; i < image_width; i++) {
            Color total_color(0, 0, 0);

            for(int sample = 0; sample < samples_per_pixel; sample++) {
                Ray ray = get_sample_ray(i, j);
                total_color += ray_color(ray, world, search_dept);
            }

            Color pixel_color = total_color / samples_per_pixel;

            auto r = linear_to_gamma(pixel_color.x());
            auto g = linear_to_gamma(pixel_color.y());
            auto b = linear_to_gamma(pixel_color.z());

            static const Interval intensity(0.000, 0.999);
            int ir = int(256 * intensity.clamp(r));
            int ig = int(256 * intensity.clamp(g));
            int ib = int(256 * intensity.clamp(b));

            i_image.setPixel(i, j, sf::Color(ir, ig, ib));
        }
    }

    /*i_image.saveToFile("render.jpg");*/
    /*return;*/

    sf::Texture t_image;
    t_image.loadFromImage(i_image);

    sf::Sprite s_image(t_image);

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();

        window.draw(s_image);

        window.display();
    }
}



void Camera::initialise() {
    int height = int(image_width / aspect_ratio);
    image_height = height < 1 ? 1 : height;

    camera_center = look_from;

    float focal_length = (look_from - look_at).length();
    double theta = deg_to_rad(vertical_fov);
    double h = std::tan(theta / 2);
    float viewport_height = 2 * h * focal_length;
    float viewport_width = viewport_height * (double(image_width) / image_height);

    w = unit_vector(look_from - look_at);
    u = unit_vector(cross(vertical_up, w));
    v = cross(w, u);

    Vec3 viewport_u = viewport_width * u;
    Vec3 viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    Vec3 viewport_upper_left = camera_center - (focal_length * w) - (viewport_u / 2) - (viewport_v / 2);
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}



Ray Camera::get_sample_ray(int i, int j) const {
    Vec3 offset = get_offset();
    Vec3 sample_ray = pixel00_loc
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

    Vec3 ray_dir = sample_ray - camera_center;
    return Ray(camera_center, ray_dir);
}



Vec3 Camera::get_offset() const {
    return Vec3(rand_db() - 0.5, rand_db() - 0.5, 0);
}



Color Camera::ray_color(const Ray& ray, const Hittable& world, int max_depth) const {
    if(max_depth <= 0)
        return Color(0, 0, 0);

    HitRecord hit_record;

    if(world.is_hit(ray, Interval(0.001, infinity), hit_record)) {
        Ray scattered;
        Color attenuation;

        if(hit_record.mat->is_scattered(ray, hit_record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, max_depth - 1);
        }

        return Color(0, 0, 0);
    }

    Vec3 unit_dir = unit_vector(ray.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);
    auto lerp = (1.0 - a) * Color(1.0, 1.0, 1.0) + (a * Color(0.5, 0.7, 1.0));

    return lerp;
}
