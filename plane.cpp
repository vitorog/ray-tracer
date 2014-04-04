#include "plane.h"

Plane::Plane(glm::vec3 position, glm::vec3 normal) :
    Primitive(position),
    normal_(normal)
{    
    this->material_ = new Material();
    this->material_->illum_ = 2;
    this->material_->ka_ = glm::vec3(0.3f,0.3f,0.3f);
    this->material_->kd_ = glm::vec3(0.6f,0.6f,0.6f);
    this->material_->ks_ = glm::vec3(0.3f,0.3f,0.3f);
    this->material_->ns_ = 64.0f;
    this->material_->tr_ = 0.0f;
}

void Plane::CheckCollision(Ray &ray)
{
    float eta = -0.0000001;
    float denom = glm::dot(ray.direction_, normal_);
    if(denom <= eta){
        float t = glm::dot(  position_ - ray.origin_, normal_) / denom;
        if(t < ray.collision_t_ && t >= 0){
            ray.collided_ = true;
            ray.collision_t_ = t;
            ray.collision_point_ = ray.origin_ + ray.collision_t_*ray.direction_;
            ray.collision_normal_ = normal_;
            ray.collided_obj_ptr_ = this;
        }
    }
}
