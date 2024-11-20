/*alias compile='g++ main.cpp -o main includes/camera/Camera.cpp includes/color/Color.cpp includes/hittable/Hittable.cpp includes/interval/Interval.cpp includes/material/Material.cpp includes/ray/Ray.cpp includes/sphere/Sphere.cpp includes/vec3/Vec3.cpp includes/hittableList/HittableList.cpp -lsfml-graphics -lsfml-window -lsfml-system'*/

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
    auto material_left = std::make_shared<Dielectric>(1.50);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.2);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.samples_per_pixel = 100;
    camera.search_dept = 50;

    camera.render(world);
}
