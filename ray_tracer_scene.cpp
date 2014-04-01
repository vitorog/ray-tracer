#include "ray_tracer_scene.h"

RayTracerScene::RayTracerScene()
{
}

void RayTracerScene::CheckCollision(Ray &ray)
{
    std::vector<RayTracerObject*>::iterator it = objects_.begin();
    for(; it != objects_.end(); it++)
    {
       (*it)->CheckCollision(ray);
    }
}
