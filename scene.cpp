#include "scene.h"

bool Triangle::CheckCollision(const Ray &ray)
{

}

Scene::Scene() :
    sphere_(Point3(0.0,0.0,-20.0),5.0f)
{   
}

bool Scene::TestSphereCollision(Ray &ray)
{
    return sphere_.CheckCollision(ray);
}

std::vector<Triangle*> Scene::CheckRayCollision(const Ray &ray)
{
    std::vector<Triangle*> collided_triangles;
    for(std::vector<Triangle>::iterator it = triangles_.begin();
        it != triangles_.end();
        it++){
        if((*it).CheckCollision(ray)){
            collided_triangles.push_back(&(*it));
        }

    }
    return collided_triangles;
}
