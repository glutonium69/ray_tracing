#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
public:
    double v[3];

    Vec3();
    Vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    double length() const;
    double length_squared() const;

    bool near_zero() const;

    static Vec3 random();
    static Vec3 random(double min, double max);

    Vec3    operator-() const;
    double  operator[](int i) const;
    double& operator[](int i);
    Vec3&   operator+=(const Vec3& vec);
    Vec3&   operator*=(const double scalar);
    Vec3&   operator/=(const double scalar);
};


using Point3 = Vec3;


std::ostream& operator<<(std::ostream& out, const Vec3& vec);


Vec3 operator+(const Vec3& vec1, const Vec3& vec2);
Vec3 operator-(const Vec3& vec1, const Vec3& vec2);
Vec3 operator*(const Vec3& vec1, const Vec3& vec2);
Vec3 operator*(const double scalar, const Vec3& vec);
Vec3 operator*(const Vec3& vec, const double scalar);
Vec3 operator/(const Vec3& vec, const double scalar);


double dot(const Vec3& vec1, const Vec3& vec2);
Vec3   cross(const Vec3& vec1, const Vec3& vec2);
Vec3   unit_vector(const Vec3& vec);
Vec3   rand_unit_vec();
Vec3   rand_on_unit_disk();
Vec3   get_reflation_dir(const Vec3& normal);
Vec3   reflect(const Vec3& ray_dir, const Vec3& normal);
Vec3   refract(const Vec3& ray_dir_normalised, const Vec3& normal, double etai_over_etat);
