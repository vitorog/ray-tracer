#ifndef RAY_TRACER_OBJECT_H
#define RAY_TRACER_OBJECT_H

#include <material.h>

#include "ray.h"

class RayTracerObject
{
public:
    RayTracerObject();
    virtual void CheckCollision(Ray &r) = 0;
    Material *material_;
};

#endif // RAY_TRACER_OBJECT_H
