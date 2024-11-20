#include "Material.hpp"
#include "../color/Color.hpp"
#include <cmath>

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



Dielectric::Dielectric(double refraction_index) : refraction_index(refraction_index) {}


bool Dielectric::is_scattered(const Ray& ray_in, const HitRecord& hit_record, Color& attenuation, Ray& scattered) const {
    attenuation = Color(1.0, 1.0, 1.0);
    double etai_over_etat = hit_record.front_face ? (1.0 / refraction_index) : refraction_index;

    Vec3 normalised_ray_in = unit_vector(ray_in.direction());
    double cos_theta = std::fmin(dot(-normalised_ray_in, hit_record.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - (cos_theta * cos_theta));

    bool cannot_refract = (etai_over_etat * sin_theta) > 1.0;
    Vec3 scattered_direction;

    if(cannot_refract)
        scattered_direction = reflect(ray_in.direction(), hit_record.normal);
    else
        scattered_direction = refract(normalised_ray_in, hit_record.normal, etai_over_etat);

    scattered = Ray(hit_record.p, scattered_direction);
    return true;
};


double Dielectric::reflectance(double cos_theta, double refraction_index) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cos_theta), 5);
}
