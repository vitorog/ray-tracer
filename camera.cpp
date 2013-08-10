#include "camera.h"

#include <cmath>

Camera::Camera() :
    position_(0.0,0.0,10.0),
    view_direction_(0.0,0.0,-1.0),
    up_direction_(0.0,1.0,0.0)
{
    w_ = view_direction_ * (-1);
    u_ = view_direction_.Cross(up_direction_);
    v_ = view_direction_.Cross(u_);

    view_direction_.Normalize();
    w_.Normalize();
    u_.Normalize();
    v_.Normalize();

    left_ = -1.0f;
    right_ = 1.0f;
    bottom_ = -1.0f;
    top_  = 1.0f;
    num_x_ = 640;
    num_y_ = 640;
    plane_distance_ = 10.0f;
    fov_x_ = 45.0f;
    fov_y_ = 45.0f;

//    fov_x_ = 90.0f;
//    fov_y_ = 90.0f;
//    float half_fov_x = fov_x_ / 2.0f;
//    float half_fov_y = fov_y_ / 2.0f;
//    left_ = - tan(half_fov_x)*plane_distance_;
//    right_ = tan(half_fov_x)*plane_distance_;
//    top_ =  tan(half_fov_y)*plane_distance_;
//    bottom_ = - tan(half_fov_y)*plane_distance_;
}

Point3 Camera::GetPixelCoordinates(int i, int j)
{
    float u = ((left_ + (right_ - left_)*(i+0.5)) / num_x_);
    float v = ((bottom_ + (top_ - bottom_)*(j+0.5)) / num_y_);
    return Point3(u,v,0);
}
