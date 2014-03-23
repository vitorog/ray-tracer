#ifndef OBJECT_H
#define OBJECT_H

#include <material.h>

#include "ray.h"
#include "mesh.h"

class Object
{
public:
    Object(glm::vec3 position);
    virtual void CheckRayCollision(Ray&);

    glm::vec3 position_;
    Mesh mesh_;
    Material material_;
};

#endif // OBJECT_H
