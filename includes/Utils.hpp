#pragma once

#include <cstdlib>
#include <limits>
/*#include <random>*/

const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

inline double deg_to_rad(double deg) {
    return deg * PI / 180.0;
}

inline double rand_db() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline double rand_db(double min, double max) {
    return min + (max-min) * rand_db();
}

/*inline double random_double() {*/
/*    static std::uniform_real_distribution<double> distribution(0.0, 1.0);*/
/*    static std::mt19937 generator;*/
/*    return distribution(generator);*/
/*}*/
