#include "Sphere.hpp"


Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat)
    : center(center), radius(std::fmax(0, radius)), mat(mat) {}


bool Sphere::is_hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const {
    Vec3 oc = center - ray.origin();
    double a = ray.direction().length_squared();
    double h = dot(ray.direction(), oc);
    double c = oc.length_squared() - radius * radius;

    double discriminant = h * h - a * c;

    if (discriminant < 0) return false;

    double sqrtd = std::sqrt(discriminant);
    double root = (h - sqrtd) / a;

    if(!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;

        if(!ray_t.surrounds(root))
            return false;
    }

    hit_record.t = root;
    hit_record.p = ray.at(root);
    hit_record.mat = mat;


    Vec3 outward_normal = (hit_record.p - center) / radius;
    hit_record.set_front_face(ray, outward_normal);

    return true;
}

