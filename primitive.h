#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <glm/vec3.hpp>

#include "ray_tracer_object.h"

class Primitive : public RayTracerObject
{
public:
    Primitive(glm::vec3 position);
    glm::vec3 position_;    
};

#endif // PRIMITIVE_H
