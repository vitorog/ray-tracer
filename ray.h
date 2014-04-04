#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

class RayTracerObject;

class Ray
{
public:
    Ray(glm::vec3 origin, glm::vec3 direction);    
    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 collision_normal_;
    float collision_t_;
    glm::vec3 collision_point_;
    bool collided_;
    RayTracerObject* collided_obj_ptr_;
};

#endif // RAY_H
