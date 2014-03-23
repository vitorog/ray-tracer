#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/vec3.hpp>
#include "material.h"

class PointLight
{
public:
    PointLight();
    Material material_;
    glm::vec3 position_;
};

#endif // POINT_LIGHT_H
