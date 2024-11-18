#include "Interval.hpp"
#include "../Utils.hpp"

Interval::Interval() : min(+infinity), max(-infinity) {}

Interval::Interval(double min, double max) : min(min), max(max) {}

double Interval::size() const { return max - min; }

bool Interval::contains(double x) const { return x >= min && x <= max; }

bool Interval::surrounds(double x) const { return x > min && x < max; }

double Interval::clamp(double x) const {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
