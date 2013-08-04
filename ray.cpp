#include "ray.h"

Ray::Ray(Point3 origin, Vec3 direction) :
    origin_(origin),
    direction_(direction),
    collided_(false),
    collision_point_(Point3()),
    collision_t_(0)
{
}
