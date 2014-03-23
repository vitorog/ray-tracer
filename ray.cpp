#include "ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction) :
    origin_(origin),
    direction_(direction),    
    collision_t_(0),
    collision_point_(glm::vec3()),
    collided_(false)
{
}
