#pragma once

#include "../interval/Interval.hpp"
#include "../ray/Ray.hpp"
#include "../vec3/Vec3.hpp"
/*#include "../material/Material.hpp"*/
#include <memory>

class Material;

class HitRecord {
public:
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> mat;
    double t;
    bool front_face;

    void set_front_face(const Ray& ray, const Vec3& outward_normal);
};


class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool is_hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const = 0;
};
