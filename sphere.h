#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "point3.h"
#include "ray.h"
#include "material.h"

class Sphere : public Object
{
public:
    Sphere(glm::vec3, float);    
    Material material_;
    float radius_;
    void CheckRayCollision(Ray&);
};

#endif // SPHERE_H
