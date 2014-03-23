#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>

#include "vec3.h"
#include "point3.h"


class Camera
{
public:
    Camera();
    glm::vec3 GetPixelCoordinates(int i,int j);
    glm::vec3 position_;
    glm::vec3 view_direction_;
    glm::vec3 up_direction_;
    glm::vec3 u_;
    glm::vec3 v_;
    glm::vec3 w_;
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
