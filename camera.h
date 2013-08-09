#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "point3.h"

class Camera
{
public:
    Camera();
    Point3 position_;
    Vec3 view_direction_;
    Vec3 up_direction_;
};

#endif // CAMERA_H
