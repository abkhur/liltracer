#ifndef LILTRACER_H
#define LILTRACER_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

/*
THE LILTRACER HEADER FILE
this is the general main header file
makes everything work and such

written by abdullah khurram on 10/3/2023
*/

// using...
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// consts
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    /*shitty rng*/
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    /*shitty rng but this time min <= x < max*/
    return min + (max-min)*random_double();
}

// common headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif