#include "sphere.h"

#include <cmath>
#include <glm/glm.hpp>

Sphere::Sphere(Point3 center, float radius) :
    Object(center),
    radius_(radius)
{
}

void Sphere::CheckRayCollision(Ray &ray)
{
    Vec3 oc = ray.origin_ - position_;    
    float A = ray.direction_.Dot(ray.direction_);
    float B = 2*(ray.direction_.Dot(oc));
    float C = (oc.Dot(oc)) - pow(radius_,2);

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

        if(!ray.collided_){
            ray.collision_t_ = t;
            ray.collision_point_ = ray.origin_ + (ray.direction_*t);
            ray.collided_ = true;
            ray.collision_normal_ = ray.collision_point_ - this->position_;
            ray.collision_normal_.Normalize();
            ray.mat_ptr_ = &this->material_;
        }else{
            if( t < ray.collision_t_){
                ray.collision_t_ = t;
                ray.collision_point_ = ray.origin_ + (ray.direction_*t);
                ray.collided_ = true;
                ray.collision_normal_ = ray.collision_point_ - this->position_;
                ray.collision_normal_.Normalize();
                ray.mat_ptr_ = &this->material_;
            }
        }
        return;
    }
    return;
}
