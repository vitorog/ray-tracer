#include "material.h"

Material::Material() :
    diffuse_(0.8,0.8,0.8),
    specular_(0.5,0.5,0.5),
    ambient_(0.1,0.1,0.1),
    shineness_(100.0f)
{
}
