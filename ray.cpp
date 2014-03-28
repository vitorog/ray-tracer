#include "ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 direction) :
    origin_(origin),
    direction_(direction),    
    collision_t_(0),
    collision_point_(glm::vec3()),
    collided_(false)
{
}

//void Object::CheckRayCollision(Ray &ray)
//{
//    ray.collision_t_ = 9999;
//    float eta = 0.0001;
//    glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), this->position_);
//    for(unsigned int i = 0; i < mesh_.vertices_index_.size(); i+=3){
//        glm::vec3 p0,p1,p2;

//        p0 = mesh_.vertices_.at(mesh_.vertices_index_.at(i) - 1);
//        p1 = mesh_.vertices_.at(mesh_.vertices_index_.at(i+1) - 1);
//        p2 = mesh_.vertices_.at(mesh_.vertices_index_.at(i+2) - 1);

//        glm::vec4 p0_m = glm::vec4(p0, 1);
//        glm::vec4 p1_m = glm::vec4(p1, 1);
//        glm::vec4 p2_m = glm::vec4(p2, 1);

//        p0 = glm::vec3(translate_matrix * p0_m);
//        p1 = glm::vec3(translate_matrix * p1_m);
//        p2 = glm::vec3(translate_matrix * p2_m);

//        glm::vec3 n0,n1,n2;
//        n0 = mesh_.normals_.at(mesh_.normals_index_.at(i) - 1);
//        n1 = mesh_.normals_.at(mesh_.normals_index_.at(i+1) - 1);
//        n2 = mesh_.normals_.at(mesh_.normals_index_.at(i+2) - 1);


//        glm::vec3 e1 = p1 - p0;
//        glm::vec3 e2 = p2 - p0;

//        glm::vec3 p = glm::cross(ray.direction_,e2);
//        float a = glm::dot(e1, p);

//        if( a < eta ){
//            continue;
//        }

//        float f = 1.0f/a;

//        glm::vec3 s = ray.origin_ - p0;
//        float u = f*glm::dot(s, p);
//        if ( u < 0.0f || u > 1.0f){
//            continue;
//        }

//        glm::vec3 q = glm::cross(s, e1);
//        float v = f * glm::dot(ray.direction_, q);
//        if ( v < 0.0f || u+v > 1.0f){
//            continue;
//        }

//        float t = f * glm::dot(e2, q);

//        if( t < ray.collision_t_ && t > 0 ){
//            ray.collided_ = true;
//            ray.collision_point_ = ray.origin_ + ray.direction_*t;
//            ray.collision_normal_ = glm::normalize(u*n0 + v*n1 + t*n2);
//        }
//    }
//    if(ray.collided_){
//        ray.mat_ptr_ = &this->material_;
//    }

//    return;
//}

