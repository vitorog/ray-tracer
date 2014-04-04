#include "mesh_object.h"

#include <object.h>

MeshObject::MeshObject(Object* obj) :
    obj_(obj)
{
    this->material_ = obj->material_;
}

void MeshObject::CheckCollision(Ray &ray)
{
    float eta = 0.0001;
    //    glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), position_);
    for(unsigned int i = 0; i < obj_->mesh_->vertices_index_.size(); i+= 3){
        glm::vec3 p0 = obj_->mesh_->vertices_.at(obj_->mesh_->vertices_index_.at(i) - 1);
        glm::vec3 p1 = obj_->mesh_->vertices_.at(obj_->mesh_->vertices_index_.at(i+1) - 1);
        glm::vec3 p2 = obj_->mesh_->vertices_.at(obj_->mesh_->vertices_index_.at(i+2) - 1);


        //        glm::vec4 p0_m = glm::vec4(p0, 1);
        //        glm::vec4 p1_m = glm::vec4(p1, 1);
        //        glm::vec4 p2_m = glm::vec4(p2, 1);

        //        p0 = glm::vec3(translate_matrix * p0_m);
        //        p1 = glm::vec3(translate_matrix * p1_m);
        //        p2 = glm::vec3(translate_matrix * p2_m);

        glm::vec3 n0,n1,n2;
        n0 = obj_->mesh_->normals_.at(obj_->mesh_->normals_index_.at(i) - 1);
        n1 = obj_->mesh_->normals_.at(obj_->mesh_->normals_index_.at(i+1) - 1);
        n2 = obj_->mesh_->normals_.at(obj_->mesh_->normals_index_.at(i+2) - 1);


        glm::vec3 e1 = p1 - p0;
        glm::vec3 e2 = p2 - p0;

        glm::vec3 p = glm::cross(ray.direction_,e2);
        float a = glm::dot(e1, p);

        if( a < eta ){
            continue;
        }

        float f = 1.0f/a;

        glm::vec3 s = ray.origin_ - p0;
        float u = f*glm::dot(s, p);
        if ( u < 0.0f || u > 1.0f){
            continue;
        }

        glm::vec3 q = glm::cross(s, e1);
        float v = f * glm::dot(ray.direction_, q);
        if ( v < 0.0f || u+v > 1.0f){
            continue;
        }

        float t = f * glm::dot(e2, q);

        if( t < ray.collision_t_ && t > 0 ){
            ray.collided_ = true;
            ray.collision_point_ = ray.origin_ + ray.direction_*t;
            ray.collision_normal_ = glm::normalize(u*n0 + v*n1 + t*n2);
            ray.collided_obj_ptr_ = this;
        }
    }

}
