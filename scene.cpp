#include "scene.h"

bool Triangle::CheckCollision(const Ray &ray)
{
    return false;
}

Scene::Scene()
{   
    Object *s1 = new Sphere(Point3(1.0,0.0,-5.0),1.0f);
    Object *s2 = new Sphere(Point3(-1.0,0.0,-5.0),1.0f);
    objects_.push_back(s1);
    objects_.push_back(s2);

}

void Scene::TestSphereCollision(Ray &ray)
{
    std::vector<Object*>::iterator it;
    for(it = objects_.begin(); it != objects_.end(); it++){
        (*it)->CheckRayCollision(ray);
    }
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
