#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H

#include <scene.h>

#include "ray_tracer_object.h"


class RayTracerScene : public Scene
{
public:
    RayTracerScene();
    std::vector<RayTracerObject*> objects_;
    void CheckCollision(Ray&);
};

#endif // RAY_TRACER_SCENE_H
