#include "Camera.hpp"
#include "../Utils.hpp"


void Camera::render(const Hittable& world) {
    initialise();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = 0; j < image_height; j++) {
        for(int i = 0; i < image_width; i++) {
            Color total_color(0, 0, 0);

            for(int sample = 0; sample < samples_per_pixel; sample++) {
                Ray ray = get_sample_ray(i, j);
                total_color += ray_color(ray, world, search_dept);
            }

            write_color(std::cout, total_color / samples_per_pixel);
        }
    }
}



void Camera::initialise() {
    int height = int(image_width / aspect_ratio);
    image_height = height < 1 ? 1 : height;

    camera_center = Point3(0, 0, 0);

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (double(image_width) / image_height);

    Vec3 viewport_u = Vec3(viewport_width, 0, 0);
    Vec3 viewport_v = Vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    Vec3 viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
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
