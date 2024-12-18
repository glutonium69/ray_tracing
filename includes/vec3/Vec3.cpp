#include "Vec3.hpp"
#include "../Utils.hpp"
#include <cmath>


Vec3::Vec3(): v{0, 0, 0} { }

Vec3::Vec3(double x, double y, double z): v{x, y, z} {}

double Vec3::x() const { return v[0]; }
double Vec3::y() const { return v[1]; }
double Vec3::z() const { return v[2]; }
double Vec3::length() const {
    return std::sqrt(length_squared());
}

double Vec3::length_squared() const {
    return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}

bool Vec3::near_zero() const {
    auto s = 1e-8;
    return (std::fabs(v[0]) < s) && (std::fabs(v[1]) < s) && (std::fabs(v[2]) < s);
}

Vec3 Vec3::random() {
    return Vec3(rand_db(), rand_db(), rand_db());
}

Vec3 Vec3::random(double min, double max) {
    return Vec3(rand_db(min, max), rand_db(min, max), rand_db(min, max));
}

Vec3 Vec3::operator-() const { return Vec3(-v[0], -v[1], -v[2]); }

double Vec3::operator[](int i) const { return v[i]; }

double& Vec3::operator[](int i) { return v[i]; }

Vec3& Vec3::operator+=(const Vec3& vec) {
    v[0] += vec.v[0];
    v[1] += vec.v[1];
    v[2] += vec.v[2];
    return *this;
}

Vec3& Vec3::operator*=(const double scalar) {
    v[0] *= scalar;
    v[1] *= scalar;
    v[2] *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(const double scalar) {
    return *this *= 1/scalar;
}



std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
    return out << "Vec2(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")\n";
}

Vec3 operator+(const Vec3& vec1, const Vec3& vec2) {
    return Vec3(vec1.v[0] + vec2.v[0], vec1.v[1] + vec2.v[1], vec1.v[2] + vec2.v[2]);
}


Vec3 operator-(const Vec3& vec1, const Vec3& vec2) {
    return Vec3(vec1.v[0] - vec2.v[0], vec1.v[1] - vec2.v[1], vec1.v[2] - vec2.v[2]);
}


Vec3 operator*(const Vec3& vec1, const Vec3& vec2) {
    return Vec3(vec1.v[0] * vec2.v[0], vec1.v[1] * vec2.v[1], vec1.v[2] * vec2.v[2]);
}


Vec3 operator*(const double scalar, const Vec3& vec) {
    return Vec3(scalar * vec[0] , scalar * vec[1], scalar * vec[2]);
}

Vec3 operator*(const Vec3& vec, const double scalar) {
    return scalar * vec;
}

Vec3 operator/(const Vec3& vec, const double scalar) {
    return (1/scalar) * vec;
}




double dot(const Vec3& vec1, const Vec3& vec2) {
    return vec1.v[0] * vec2.v[0]
         + vec1.v[1] * vec2.v[1]
         + vec1.v[2] * vec2.v[2];
}

Vec3 cross(const Vec3& vec1, const Vec3& vec2) {
    return Vec3(vec1.v[1] * vec2.v[2] - vec1.v[2] * vec2.v[1],
                vec1.v[2] * vec2.v[0] - vec1.v[0] * vec2.v[2],
                vec1.v[0] * vec2.v[1] - vec1.v[1] * vec2.v[0]);
}

Vec3 unit_vector(const Vec3& vec) {
    return vec / vec.length();
}

Vec3 rand_unit_vec() {
    while(true) {
        Vec3 rand_vec = Vec3::random(-1, 1);
        double length_squared = rand_vec.length_squared();
        if(10e-160 < length_squared && length_squared <= 1)
            return rand_vec / std::sqrt(length_squared);
    }
}

Vec3 get_reflation_dir(const Vec3& normal) {
   Vec3 on_unit_sphere = rand_unit_vec();
    if(dot(on_unit_sphere, normal) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

Vec3 reflect(const Vec3& ray_dir, const Vec3& normal) {
    return ray_dir - 2 * dot(ray_dir, normal) * normal;
}

Vec3 refract(const Vec3& ray_dir_normalised, const Vec3& normal, double etai_over_etat) {
    double cos_theta = std::fmin(dot(-ray_dir_normalised, normal), 1.0);
    Vec3 ray_out_perpendicular = etai_over_etat * (ray_dir_normalised + cos_theta * normal);
    Vec3 ray_out_parallel = -std::sqrt(std::fabs(1.0 - ray_out_perpendicular.length_squared())) * normal;

    return ray_out_perpendicular + ray_out_parallel;
}


/*Vec3 rand_on_unit_disk() {*/
/*    while(true) {*/
/*        Vec3 rand_vec = Vec3(rand_db(-1, 1), rand_db(-1, 1), 0);*/
/**/
/*        if(rand_vec.length_squared() < 1)*/
/*            return rand_vec;*/
/*    }*/
/*}*/

Vec3 rand_on_unit_disk() {
    while (true) {
        auto p = Vec3(rand_db(-1,1), rand_db(-1,1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}
