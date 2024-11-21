#pragma once


#include "../color/Color.hpp"
#include "../hittable/Hittable.hpp"
#include "../ray/Ray.hpp"
#include "../vec3/Vec3.hpp"
#include "../material/Material.hpp"


class Camera {
public:
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 10;
    int search_dept = 10;

    double vertical_fov = 90;  // Vertical view angle (field of view)
    Point3 look_from = Point3(0, 0, 0);
    Point3 look_at = Point3(0, 0, -1);
    Vec3 vertical_up = Vec3(0, 1, 0);

    void render(const Hittable& world);

private:
    int image_height;
    Point3 camera_center;
    Point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    Vec3 u, v, w; // Camera frame basis vectors

    void initialise();

    Ray get_sample_ray(int i, int j) const;

    Vec3 get_offset() const;

    Color ray_color(const Ray& ray, const Hittable& world, int max_depth) const;
};
