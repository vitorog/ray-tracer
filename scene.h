#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../shade-framework/model.h"

#include "object.h"
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
    Vec3 normal;
    bool CheckCollision(Ray&);
};

class Scene
{
public:
    Scene();
    Scene(std::string scene_path);
    void TestSphereCollision(Ray& );
    std::vector<Triangle*> CheckRayCollision(Ray&);
    std::vector<Triangle*> triangles_;
    PointLight light_;
    std::vector<Object*> objects_;
    Camera camera_;
    Model scene_model_;
};

#endif // SCENE_H
