#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "point3.h"

class Camera
{
public:
    Camera();
    Point3 GetPixelCoordinates(int i,int j);
    Point3 position_;
    Vec3 view_direction_;
    Vec3 up_direction_;
    Vec3 u_;
    Vec3 v_;
    Vec3 w_;
    float left_;
    float right_;
    float top_;
    float bottom_;
    float plane_distance_; //View plane distance
    float num_x_; //Horizontal pixel count / Image width
    float num_y_; //Vertical pixel count / Image height
    float fov_x_;
    float fov_y_;
};

#endif // CAMERA_H
