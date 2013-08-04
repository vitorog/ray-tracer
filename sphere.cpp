#include "sphere.h"

#include <cmath>

Sphere::Sphere(Point3 center, float radius) :
    center_(center),
    radius_(radius)
{
}

bool Sphere::CheckCollision(Ray &ray)
{
    Vec3 oc = ray.origin_ - center_;
    //oc.Normalize();
    float c = oc.Dot(oc) - pow(radius_,2);
    float b = ray.direction_.Dot(oc);
    float delta = pow(b,2) - c;
    if(delta < 0){
        return ray.collided_;
    }else if(delta == 0){
        float t = - b + sqrt(delta);
        ray.collided_ = true;
        ray.collision_t_ = t;
        ray.collision_point_ = (ray.origin_ + (ray.direction_*t));
    }else{
        float t1 = - b + sqrt(delta);
        float t2 = - b + sqrt(delta);
        ray.collided_ = true;
        float t = t1 < t2 ? t1 : t2;
        ray.collision_t_ = t;
        ray.collision_point_ = (ray.origin_ + (ray.direction_*t));
    }
    return ray.collided_;
}
