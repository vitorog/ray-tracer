#include "scene.h"

bool Triangle::CheckCollision(const Ray &ray)
{

}

Scene::Scene()
{
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
