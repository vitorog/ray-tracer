#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "vec3.h"
#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include "light.h"

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
    void TestSphereCollision(Ray& );
    std::vector<Triangle*> CheckRayCollision(const Ray&);   
    std::vector<Triangle> triangles_;
    PointLight light_;
    std::vector<Sphere*> spheres_;
    Camera camera_;
};

#endif // SCENE_H
