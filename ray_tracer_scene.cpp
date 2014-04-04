#include "ray_tracer_scene.h"

RayTracerScene::RayTracerScene()
{
}

void RayTracerScene::CheckCollision(Ray &ray)
{
    std::vector<RayTracerObject*>::iterator it = objects_.begin();
    for(; it != objects_.end(); it++)
    {
        if(ray.collided_obj_ptr_ != NULL && ray.collided_obj_ptr_ == (*it)){
            continue;
        }
        (*it)->CheckCollision(ray);
    }
}
