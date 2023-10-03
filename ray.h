#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/*
the (in)famous ray class, one that all raytracers are required to have

some explanation:
given a function p(t) = A+tb, p is a 3d position along a 3d line
A is the ray origin and b is the ray direction
the parameter t is a double that allows the ray to move in any direction along this line
hence, rays :)

written by:
abdullah khurram

10/3/2023
*/

class ray {
    public:
        ray() {}

        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

        point3 origin() const { return orig; }
        vec3 direction() const { return dir; }

        point3 at(double t) const {
            return orig + t*dir;
        }
    private:
        point3 orig;
        vec3 dir;
};

#endif