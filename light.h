#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "vec3.h"
#include "point3.h"
#include "material.h"

class PointLight
{
public:
    PointLight();
    Material material_;
    Point3 position_;
};

#endif // POINT_LIGHT_H
