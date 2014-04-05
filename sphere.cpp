#include "sphere.h"

#include <cmath>
#include <glm/glm.hpp>

Sphere::Sphere(glm::vec3 center, float radius) :
    Primitive(center),
    radius_(radius)
{
    Material *m = new Material();
    this->material_ = m;
    m->illum_ = 2;
    m->ka_ = glm::vec3(0.2f,0.2f,0.2f);
    m->kd_ = glm::vec3(0.8f,0.8f,0.8f);
    m->ks_ = glm::vec3(0.4f,0.4f,0.4f);
    m->ns_ = 64.0f;
    m->tr_ = 0.0f;
}

void Sphere::CheckCollision(Ray& ray)
{
    glm::vec3 oc = ray.origin_ -  position_;
    float A = glm::dot(ray.direction_, ray.direction_);
    float B = 2*(glm::dot(ray.direction_, oc));
    float C = (glm::dot(oc,oc)) - pow( radius_,2);

    float delta = pow(B,2) - 4*A*C;
    if(delta >= 0){
        float t1;
        float t2;
        if(delta == 0){
            t1 = (-B + sqrt(delta))/ 2 * A;
            t2 = t1;
            if(t1 < 0){
                return;
            }
        }else{
            t1 = (-B + sqrt(delta))/ 2 * A;
            t2 = (-B - sqrt(delta))/ 2 * A;
            if(t1 < 0 || t2 < 0){
                return;
            }
        }
        float t = t1 < t2 ? t1 : t2;
        if( t < ray.collision_t_ && t > 0){
            ray.collision_t_ = t;
            ray.collision_point_ = ray.origin_ + (ray.direction_*t);
            ray.collided_ = true;
            ray.collision_normal_ = glm::normalize(ray.collision_point_ -  position_);
            ray.collided_obj_ptr_ =  this;
        }
    }
}
