#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Material;

class Sphere : public Primitive
{
public:
    Sphere(glm::vec3, float);
    float radius_;  
    void CheckCollision(Ray &);
};

#endif // SPHERE_H
