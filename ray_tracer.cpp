#include "ray_tracer.h"

#include <cmath>

#include "light.h"

#include "vec3.h"

#include "glm/vec3.hpp"

RayTracer::RayTracer()
    :gl_widget_(NULL),
     gl_renderer_(NULL),
      width_(640),
      height_(640),
      max_depth_(1)
      ,test_scene_("F:\\Development\\Repositories\\Personal\\Builds\\raytracer-windows-debug\\debug\\test.obj")
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

#include "sphere.h"
#include "debug.h"


glm::vec3 CalculatePhongLighting(Ray& ray, PointLight& light, Camera& camera, Material& material)
{
    glm::vec3 ka_result = material.ka_
            * light.material_.ka_;
    glm::vec3 kd_result = material.kd_
            * light.material_.kd_;
    glm::vec3 ks_result = material.ks_
            * light.material_.ks_;

    //TOD

    glm::vec3 light_dir = glm::normalize(light.position_ - ray.collision_point_);

    float NdotL = std::max(glm::dot(ray.collision_normal_,light_dir),0.0f);

    glm::vec3 viewer_vec = glm::normalize(camera.position_ - ray.collision_point_);


    glm::vec3 reflection_vec = glm::normalize(ray.collision_normal_*(2*(glm::dot(light_dir,ray.collision_normal_))) -
            light_dir);

    float RdotV = pow(std::max(glm::dot(viewer_vec,reflection_vec),0.0f), material.ns_);

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
            float x_coordinate = x - (width_/2.0f);
            float y_coordinate = y - (height_/2.0f);
            glm::vec3 pixel_coordinates = test_scene_.camera_.GetPixelCoordinates(x_coordinate,y_coordinate);
            glm::vec3 ray_direction = glm::normalize(test_scene_.camera_.u_*pixel_coordinates.x
                    + test_scene_.camera_.v_ * pixel_coordinates.y
                    - test_scene_.camera_.w_ * test_scene_.camera_.plane_distance_);
            glm::vec3 final_color = CastRay(test_scene_.camera_.position_,ray_direction, depth);
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
    test_scene_.CheckRayCollision(ray);
    if(ray.collided_){
//        return glm::vec3(1.0f,0.0f,0.0f);
        glm::vec3 point_light_dir = glm::normalize(test_scene_.light_.position_ - ray.collision_point_);
        bool shadow = CastShadowRay(ray.collision_point_,point_light_dir);
        if(shadow){
            return glm::vec3(0.0f,0.0f,0.0f);
        }else{
            if(depth < max_depth_){
                float c1 = (-1)*glm::dot(ray.collision_normal_,ray.direction_);
                glm::vec3 reflected_ray_dir = ray.direction_ + (ray.collision_normal_ * c1 * 2.0f);
                glm::vec3 reflected_ray_pos = ray.collision_point_;
                return CalculatePhongLighting(ray,test_scene_.light_,test_scene_.camera_,*ray.mat_ptr_)
                        + CastRay(reflected_ray_pos,reflected_ray_dir, depth + 1);
            }else{
                return CalculatePhongLighting(ray,test_scene_.light_,test_scene_.camera_,*ray.mat_ptr_);
            }
        }
    }else{
        return glm::vec3(0.0f,0.0f,0.0f);
    }
}

bool RayTracer::CastShadowRay(glm::vec3 origin, glm::vec3 direction)
{
     Ray ray(origin,direction);
     test_scene_.CheckRayCollision(ray);
     return ray.collided_;
}
