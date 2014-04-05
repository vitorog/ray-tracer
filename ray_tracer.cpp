#include "ray_tracer.h"

#include <glm/vec3.hpp>
#include <cmath>
#include <scene.h>

#include "ray.h"

RayTracer::RayTracer()
    :gl_widget_(NULL),
      gl_renderer_(NULL),
      width_(640),
      height_(640),
      max_depth_(2),
      clear_color_(0.2,0.2,0.2),
      current_scene_(NULL)
{
}

RayTracer::~RayTracer()
{
    if(gl_widget_ != NULL){
        delete gl_widget_;
    }
    if(gl_renderer_ != NULL){
        delete gl_renderer_;
    }
}

void RayTracer::Initialize()
{
    gl_widget_ = new GlWidget();
    gl_widget_->setFixedSize(width_,height_);
    gl_renderer_ = new GlRenderer(width_,height_);
    gl_widget_->SetRenderer(gl_renderer_);
    gl_widget_->show();
}

glm::vec3 CalculatePhongLighting(Ray& ray, PointLight* light, Camera* camera, Material *material)
{
    glm::vec3 ka_result = material->ka_
            * light->material_.ka_;
    glm::vec3 kd_result = material->kd_
            * light->material_.kd_;
    glm::vec3 ks_result = material->ks_
            * light->material_.ks_;

    glm::vec3 light_dir = glm::normalize(light->position_ - ray.collision_point_);

    float NdotL = std::max(glm::dot(ray.collision_normal_,light_dir),0.0f);

    glm::vec3 viewer_vec = glm::normalize(camera->position_ - ray.collision_point_);


    glm::vec3 reflection_vec = glm::normalize((2*(glm::dot(light_dir,ray.collision_normal_)) * ray.collision_normal_)
                                              -  light_dir);

    float RdotV = pow(std::max(glm::dot(viewer_vec,reflection_vec),0.0f), material->ns_);

    glm::vec3 final_color = ka_result + (kd_result*NdotL) + (ks_result*RdotV);
    final_color.x = std::min(final_color.x,1.0f);
    final_color.y = std::min(final_color.y,1.0f);
    final_color.z = std::min(final_color.z,1.0f);
    return final_color;
}

void RayTracer::CastRays()
{    
    GLubyte rgba_texture[height_][width_][4];
    int depth = 1;
    for(int y=0;y<height_;y++){
        for(int x=0;x<width_;x++){
            glm::vec3 final_color = glm::vec3(0.0f,0.0f,0.0f);
            if(current_scene_ != NULL){
                int y_coord = int(y - (height_ / 2.0f));
                int x_coord = int(x - (width_ / 2.0f));
                glm::vec3 screen_point = current_scene_->camera_->GetScreenPlanePoint(x_coord,y_coord);
                glm::vec3 ray_direction = glm::normalize(screen_point - current_scene_->camera_->position_);
                final_color += CastRay(current_scene_->camera_->position_,ray_direction, depth);
            }else{
                final_color = clear_color_;
            }
            rgba_texture[y][x][0] = 255*final_color.x;
            rgba_texture[y][x][1] = 255*final_color.y;
            rgba_texture[y][x][2] = 255*final_color.z;
            rgba_texture[y][x][3] = 255;
        }
    }
    gl_renderer_->SetTexture(&rgba_texture[0][0][0]);
}

glm::vec3 RayTracer::CastRay(glm::vec3 origin, glm::vec3 direction, int depth)
{
    Ray ray(origin,direction);
    current_scene_->CheckCollision(ray);
    if(ray.collided_){
        glm::vec3 point_light_dir = glm::normalize(current_scene_->light_->position_ - ray.collision_point_);
        glm::vec3 color = CalculatePhongLighting(ray,current_scene_->light_,current_scene_->camera_,ray.collided_obj_ptr_->material_)
                * CastShadowRay(ray.collision_point_,point_light_dir);
        if(depth < max_depth_ && ray.collided_obj_ptr_->material_->illum_ == 3){
            glm::vec3 reflected_ray_dir = glm::normalize(ray.direction_
                                                         - (2.0f * glm::dot (ray.collision_normal_, ray.direction_)
                                                            * ray.collision_normal_));
            glm::vec3 reflected_ray_pos = ray.collision_point_;
            color += CastRay(reflected_ray_pos,reflected_ray_dir, depth + 1);
        }
        color.x = std::max(std::min(color.x , 1.0f),0.0f);
        color.y = std::max(std::min(color.y , 1.0f),0.0f);
        color.z = std::max(std::min(color.z , 1.0f),0.0f);
        return color;
    }else{
        if(depth == 1){
            return clear_color_;
        }else{
            return glm::vec3(0.0f,0.0f,0.0f);
        }
    }
}

float RayTracer::CastShadowRay(glm::vec3 origin, glm::vec3 direction)
{
    Ray ray(origin,direction);
    current_scene_->CheckCollision(ray);
    if(ray.collided_){
        glm::vec3 viewer_vec = glm::normalize(current_scene_->camera_->position_ - ray.collision_point_);
        if(glm::dot(viewer_vec, current_scene_->camera_->view_direction_) > 0){
            ray.collided_ = false; //Collision point is behind the viewer
        }
    }
    if(ray.collided_){
        return 0.0f;
    }else{
        return 1.0f;
    }
}

void RayTracer::SetScene(RayTracerScene *s)
{
    current_scene_ = s;
}
