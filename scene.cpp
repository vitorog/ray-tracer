#include "scene.h"

bool Triangle::CheckCollision(const Ray &ray)
{
}

Scene::Scene()
{   
    Sphere *s1 = new Sphere(Point3(1.0,0.0,-5.0),1.0f);
    Sphere *s2 = new Sphere(Point3(-1.0,0.0,-5.0),1.0f);
    spheres_.push_back(s1);
    spheres_.push_back(s2);

}

void Scene::TestSphereCollision(Ray &ray)
{
    std::vector<Sphere*>::iterator it;
    for(it = spheres_.begin(); it != spheres_.end(); it++){
        (*it)->CheckCollision(ray);
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
