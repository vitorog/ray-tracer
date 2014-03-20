#include "ray.h"

Ray::Ray(Point3 origin, Vec3 direction) :
    origin_(origin),
    direction_(direction),    
    collision_t_(0),
    collision_point_(Point3()),
    collided_(false)
{
}
