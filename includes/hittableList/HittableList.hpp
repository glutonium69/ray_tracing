#pragma once

#include "../hittable/Hittable.hpp"
#include "../interval/Interval.hpp"
#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList();

    HittableList(std::shared_ptr<Hittable> object);

    void clear();

    void add(std::shared_ptr<Hittable> object);

    bool is_hit(const Ray& ray, Interval ray_t, HitRecord& hit_record) const override;
};
