#include "scene.h"

#include "../shade-framework/scene_loader.h"

Scene::Scene()
{   
    Object *s1 = new Sphere(glm::vec3(1.0,0.0,-15.0),1.0f);
    Object *s2 = new Sphere(glm::vec3(-1.0,0.0,-15.0),1.0f);
    objects_.push_back(s1);
    objects_.push_back(s2);

}

Scene::Scene(std::string scene_path)
{    
    SceneLoader m;
    if(m.Load(scene_path) == 0){
        //This is just a temporary loader...
        Object *o = new Object(glm::vec3(0.0f,0.0f,-10.0f));
        o->mesh_.normals_ = m.normals_;
        o->mesh_.normals_index_ = m.normals_index_;
        o->mesh_.text_coords_ = m.text_coords_;
        o->mesh_.text_coords_index_ = m.text_coords_index_;
        o->mesh_.vertices_ = m.vertices_;
        o->mesh_.vertices_index_ = m.vertices_index_;
        o->material_ = m.materials_[0];
        objects_.push_back(o);
    }
}

void Scene::CheckRayCollision(Ray &ray)
{
    std::vector<Object*>::iterator it = objects_.begin();
    for(; it != objects_.end(); it++){
        Object* o = (*it);
        o->CheckRayCollision(ray);
    }
}
