#include "plane.h"

Plane::Plane(glm::vec3 position, glm::vec3 normal) :
    Primitive(position),
    normal_(normal)
{
    Material *m = new Material();
    this->material_ = m;
    m->illum_ = 2;
    m->ka_ = glm::vec3(1.0f,0.3f,0.3f);
    m->kd_ = glm::vec3(1.0f,0.3f,0.3f);
    m->ks_ = glm::vec3(0.3f,0.3f,0.3f);
    m->ns_ = 64.0f;
    m->tr_ = 0.0f;
}

void Plane::CheckCollision(Ray &ray)
{
    float eta = 0.0000009;
    float denom = glm::dot(normal_ , ray.direction_);
    if(denom >= eta){
        float t = glm::dot(position_ - ray.origin_, normal_) / denom;
        if(t < ray.collision_t_ && t >= 0){
            ray.collided_ = true;
            ray.collision_t_ = t;
            ray.collision_point_ = ray.origin_ + ray.collision_t_*ray.direction_;
            ray.collision_normal_ = normal_;
            ray.mat_ptr_ = material_;
        }
    }
}
