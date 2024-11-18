#include "HittableList.hpp"


HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> object) { add(object); }

void HittableList::clear() { objects.clear(); }

void HittableList::add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

bool HittableList::is_hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const {
    HitRecord temp_record;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const auto& object : objects) {
        if (object->is_hit(ray, Interval(ray_t.min, closest_so_far), temp_record)) {
            hit_anything = true;
            closest_so_far = temp_record.t;
            hit_record = temp_record;
        }
    }

    return hit_anything;
}
