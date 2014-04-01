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
      clear_color_(0.4,0.4,0.7),
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

    //TODO

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
            glm::vec3 final_color;
            if(current_scene_ != NULL){
                int y_coord = int(y - (height_ / 2.0f));
                int x_coord = int(x - (width_ / 2.0f));
                glm::vec3 screen_point = current_scene_->camera_->GetScreenPlanePoint(x_coord,y_coord);
                glm::vec3 ray_direction = glm::normalize(screen_point - current_scene_->camera_->position_);
                final_color = CastRay(current_scene_->camera_->position_,ray_direction, depth);
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
    ray.CheckCollision(current_scene_);
    if(ray.collided_){
        glm::vec3 point_light_dir = glm::normalize(current_scene_->light_->position_ - ray.collision_point_);
        bool shadow = CastShadowRay(ray.collision_point_,point_light_dir);
        if(shadow){
            return glm::vec3(0.0f,0.0f,0.0f);
        }else{
            if(depth < max_depth_){
                if(ray.mat_ptr_->illum_ == 2){
                    return CalculatePhongLighting(ray,current_scene_->light_,current_scene_->camera_,ray.mat_ptr_);
                }else if(ray.mat_ptr_->illum_ == 3){
                    float c1 = (-1)*glm::dot(ray.collision_normal_,ray.direction_);
                    glm::vec3 reflected_ray_dir = ray.direction_ + (ray.collision_normal_ * c1 * 2.0f);
                    glm::vec3 reflected_ray_pos = ray.collision_point_;
                    return CalculatePhongLighting(ray,current_scene_->light_,current_scene_->camera_,ray.mat_ptr_)
                            + 0.5f*CastRay(reflected_ray_pos,reflected_ray_dir, depth + 1);
                }
            }else{
                return CalculatePhongLighting(ray,current_scene_->light_,current_scene_->camera_,ray.mat_ptr_);
            }
        }
    }else{
        return clear_color_;
    }
}

bool RayTracer::CastShadowRay(glm::vec3 origin, glm::vec3 direction)
{
    Ray ray(origin,direction);
    ray.CheckCollision(current_scene_);
    return ray.collided_;
}

void RayTracer::SetScene(Scene *s)
{
    current_scene_ = s;
}
