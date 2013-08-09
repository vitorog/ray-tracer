#ifndef SPHERE_H
#define SPHERE_H

#include "point3.h"
#include "ray.h"
#include "material.h"

class Sphere
{
public:
    Sphere(Point3, float);
    Point3 center_;
    Material material_;
    float radius_;
    bool CheckCollision(Ray&);
};

#endif // SPHERE_H
