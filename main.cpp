#include <memory>

#include "includes/Utils.hpp"
#include "includes/camera/Camera.hpp"
#include "includes/color/Color.hpp"
#include "includes/hittableList/HittableList.hpp"
#include "includes/material/Material.hpp"
#include "includes/sphere/Sphere.hpp"
#include "includes/vec3/Vec3.hpp"


int main() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = rand_db();
            Point3 center(a + 0.9 * rand_db(), 0.2, b + 0.9 * rand_db());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = rand_db(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    Camera camera;

    
    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 1200;
    camera.samples_per_pixel = 500;
    camera.search_depth      = 50;

    camera.vertical_fov = 20;
    camera.look_from    = Point3(13,2,3);
    camera.look_at      = Point3(0,0,0);
    camera.vertical_up  = Vec3(0,1,0);

    camera.defocus_angle  = 0.6;
    camera.focus_distance = 10.0;

    camera.render(world);
}
