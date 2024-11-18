#pragma once

class Interval {
public:
    double min, max;

    Interval();
    Interval(double min, double max);

    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;
    double clamp(double x) const;

    static const Interval empty, universe;
};
