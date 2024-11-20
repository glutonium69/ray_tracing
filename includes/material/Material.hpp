#pragma once

#include "../color/Color.hpp"
#include "../hittable/Hittable.hpp"
#include "../ray/Ray.hpp"

class Material {
public:
    virtual ~Material() = default;

    virtual bool is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const;
};


class Lambertian : public Material {
public:
    Lambertian(const Color& albedo);

    bool is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;

private:
    Color albedo;
};


class Metal : public Material {
public:
    Metal(const Color& albdeo, double fuzz);

    bool is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;

private:
    Color albedo;
    double fuzz;
};


class Dielectric : public Material {
public:
    Dielectric(double refraction_index);

    bool is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const override;

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;
};
