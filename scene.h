#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "vec3.h"
#include "point3.h"
#include "ray.h"

class Triangle{
public:
    Point3 a;
    Point3 b;
    Point3 c;
    bool CheckCollision(const Ray&);
};

class Scene
{
public:
    Scene();
    std::vector<Triangle*> CheckRayCollision(const Ray&);
    Point3 observer_pos_;
    Point3 light_position_;
    std::vector<Triangle> triangles_;
};

#endif // SCENE_H
