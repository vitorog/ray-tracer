#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
    Ray(Vec3 origin, Vec3 direction);
    Vec3 origin_;
    Vec3 direction_;
};

#endif // RAY_H
