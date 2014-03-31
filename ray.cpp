#include "ray.h"

#include <scene.h>
#include <object.h>
#include <material.h>

#include <glm/gtc/matrix_transform.hpp>

Ray::Ray(glm::vec3 origin, glm::vec3 direction) :
    origin_(origin),
    direction_(direction),
    collision_t_(99999),
    collision_point_(glm::vec3()),
    collided_(false)
{
}


void Ray::CheckCollision(Scene *s)
{
    std::vector<Object*>::iterator it = s->objects_.begin();
    for(; it != s->objects_.end(); it++)
    {
        CheckCollision((*it));
    }
}

void Ray::CheckCollision(Object *o)
{
    float eta = 0.0001;
//    glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), o->position_);
    for(unsigned int i = 0; i < o->mesh_->vertices_index_.size(); i+= 3){
        glm::vec3 p0 = o->mesh_->vertices_.at(o->mesh_->vertices_index_.at(i) - 1);
        glm::vec3 p1 = o->mesh_->vertices_.at(o->mesh_->vertices_index_.at(i+1) - 1);
        glm::vec3 p2 = o->mesh_->vertices_.at(o->mesh_->vertices_index_.at(i+2) - 1);


//        glm::vec4 p0_m = glm::vec4(p0, 1);
//        glm::vec4 p1_m = glm::vec4(p1, 1);
//        glm::vec4 p2_m = glm::vec4(p2, 1);

//        p0 = glm::vec3(translate_matrix * p0_m);
//        p1 = glm::vec3(translate_matrix * p1_m);
//        p2 = glm::vec3(translate_matrix * p2_m);

        glm::vec3 n0,n1,n2;
        n0 = o->mesh_->normals_.at(o->mesh_->normals_index_.at(i) - 1);
        n1 = o->mesh_->normals_.at(o->mesh_->normals_index_.at(i+1) - 1);
        n2 = o->mesh_->normals_.at(o->mesh_->normals_index_.at(i+2) - 1);


        glm::vec3 e1 = p1 - p0;
        glm::vec3 e2 = p2 - p0;

        glm::vec3 p = glm::cross(direction_,e2);
        float a = glm::dot(e1, p);

        if( a < eta ){
            continue;
        }

        float f = 1.0f/a;

        glm::vec3 s = origin_ - p0;
        float u = f*glm::dot(s, p);
        if ( u < 0.0f || u > 1.0f){
            continue;
        }

        glm::vec3 q = glm::cross(s, e1);
        float v = f * glm::dot(direction_, q);
        if ( v < 0.0f || u+v > 1.0f){
            continue;
        }

        float t = f * glm::dot(e2, q);

        if( t < collision_t_ && t > 0 ){
            collided_ = true;
            collision_point_ = origin_ + direction_*t;
            collision_normal_ = glm::normalize(u*n0 + v*n1 + t*n2);
            mat_ptr_ = o->material_;
        }
    }    
}
