#pragma once

#include "../hittable/Hittable.hpp"
#include "../interval/Interval.hpp"
#include "../vec3/Vec3.hpp"
#include <cmath>
#include <memory>

class Sphere : public Hittable {
public:
    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);

    bool is_hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const override;

private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat;
};
