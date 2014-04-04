#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"

class Plane : public Primitive
{
public:
    Plane(glm::vec3 position, glm::vec3 normal);
    glm::vec3 normal_;
    void CheckCollision(Ray &);
    float max_t_;
};

#endif // PLANE_H
