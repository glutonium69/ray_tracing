#include <memory>

#include "includes/camera/Camera.hpp"
#include "includes/color/Color.hpp"
#include "includes/hittableList/HittableList.hpp"
#include "includes/material/Material.hpp"
#include "includes/sphere/Sphere.hpp"
#include "includes/vec3/Vec3.hpp"


int main() {
    HittableList world;

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(1.50);
    auto material_bubble = std::make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera camera;

    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 400;
    camera.samples_per_pixel = 100;
    camera.search_depth      = 50;

    camera.vertical_fov = 20;
    camera.look_from    = Point3(-2, 2, 1);
    camera.look_at      = Point3( 0, 0, -1);
    camera.vertical_up  = Vec3(0, 1, 0);

    camera.defocus_angle  = 10.0;
    camera.focus_distance = 3.4;

    camera.render(world);
}
