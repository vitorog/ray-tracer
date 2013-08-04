#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "point3.h"

class Ray
{
public:
    Ray(Point3 origin, Vec3 direction);
    Point3 origin_;
    Vec3 direction_;
    float collision_t_;
    Point3 collision_point_;
    bool collided_;
};

#endif // RAY_H
