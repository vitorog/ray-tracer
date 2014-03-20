#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

class Material
{
public:
    Material();
    Vec3 diffuse_;
    Vec3 specular_;
    Vec3 ambient_;
    float shineness_;
};

#endif // MATERIAL_H
