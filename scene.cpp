#include "scene.h"

#include "../shade-framework/scene_loader.h"

bool Triangle::CheckCollision(Ray &ray)
{
    float t = 0;
    ray.collision_t_ = t;
    ray.collision_point_ = ray.origin_ + (ray.direction_*t);
    ray.collided_ = true;
//    ray.collision_normal_ = ray.collision_point_ - this->position_;
//    ray.collision_normal_.Normalize();
    ray.mat_ptr_ = new Material();
    return true;
}

Scene::Scene()
{   
    Object *s1 = new Sphere(Point3(1.0,0.0,-5.0),1.0f);
    Object *s2 = new Sphere(Point3(-1.0,0.0,-5.0),1.0f);
    objects_.push_back(s1);
    objects_.push_back(s2);

}

Scene::Scene(std::string scene_path)
{
    SceneLoader m;
    m.Load(scene_path);
    for(int i = 0; i < m.vertices_index_.size(); i+= 3)
    {
        Triangle *t = new Triangle();
        t->a.x_ = m.vertices_[m.vertices_index_[i]].x;
        t->a.y_ = m.vertices_[m.vertices_index_[i]].y;
        t->a.z_ = m.vertices_[m.vertices_index_[i]].z;

        t->b.x_ = m.vertices_[m.vertices_index_[i+1]].x;
        t->b.y_ = m.vertices_[m.vertices_index_[i+1]].y;
        t->b.z_ = m.vertices_[m.vertices_index_[i+1]].z;

        t->c.x_ = m.vertices_[m.vertices_index_[i+2]].x;
        t->c.y_ = m.vertices_[m.vertices_index_[i+2]].y;
        t->c.z_ = m.vertices_[m.vertices_index_[i+2]].z;

        Vec3 ba = t->b - t->a;
        Vec3 ca = t->c - t->a;
        t->normal = ba.Cross(ca);
        triangles_.push_back(t);
    }
}

void Scene::TestSphereCollision(Ray &ray)
{
    std::vector<Object*>::iterator it;
    for(it = objects_.begin(); it != objects_.end(); it++){
        (*it)->CheckRayCollision(ray);
    }
}

std::vector<Triangle*> Scene::CheckRayCollision(Ray &ray)
{
    std::vector<Triangle*> collided_triangles;
    for(std::vector<Triangle*>::iterator it = triangles_.begin();
        it != triangles_.end();
        it++){
        if((*it)->CheckCollision(ray)){
            collided_triangles.push_back(*it);
        }
    }
    return collided_triangles;
}
