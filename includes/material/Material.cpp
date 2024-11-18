#include "Material.hpp"
#include "../color/Color.hpp"

bool Material::is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const {
    return false;
}



Lambertian::Lambertian(const Color& albedo) : albedo(albedo) {}

bool Lambertian::is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const {
    Vec3 scatter_dir = hit_record.normal + rand_unit_vec();

    if(scatter_dir.near_zero())
        scatter_dir = hit_record.normal;

    scattered = Ray(hit_record.p, scatter_dir);
    attenuation = albedo;
    return true;
}



Metal::Metal(const Color& albdeo, double fuzz) : albedo(albdeo), fuzz(fuzz) {}

bool Metal::is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(ray_in.direction(), hit_record.normal);
    reflected = unit_vector(reflected) + (fuzz * rand_unit_vec());
    scattered = Ray(hit_record.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), hit_record.normal) > 0);
}
