#ifndef OBJECT_H
#define OBJECT_H

#include "point3.h"
#include "ray.h"

class Object
{
public:
    Object(Point3 position);
    Point3 position_;
    virtual void CheckRayCollision(Ray&);
};

#endif // OBJECT_H
