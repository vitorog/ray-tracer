#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../shade-framework/scene_loader.h"

#include "object.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "light.h"


class Scene
{
public:
    Scene();
    Scene(std::string scene_path);    
    void CheckRayCollision(Ray&);
    PointLight light_;
    std::vector<Object*> objects_;
    Camera camera_;
    SceneLoader loader_;
};

#endif // SCENE_H
