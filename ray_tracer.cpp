#include "ray_tracer.h"

#include <cmath>

RayTracer::RayTracer()
    : gl_renderer_(NULL),
      gl_widget_(NULL),
      width_(640),
      height_(640)
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
    gl_renderer_ = new GlRenderer(width_,height_);
    gl_widget_->SetRenderer(gl_renderer_);
    gl_widget_->show();
}

#include "sphere.h"
#include "debug.h"


Vec3 CalculatePhongLighting(Ray& ray, Scene& scene)
{
    Vec3 ambient_result = scene.sphere_.material_.ambient_
            * scene.light_.material_.ambient_;
    Vec3 diffuse_result = scene.sphere_.material_.diffuse_
            * scene.light_.material_.diffuse_;
    Vec3 specular_result = scene.sphere_.material_.specular_
            * scene.light_.material_.specular_;
    //TODO
    Vec3 collision_normal = ray.collision_point_ - scene.sphere_.center_;
    collision_normal.Normalize();
    Vec3 light_dir = scene.light_.position_ - ray.collision_point_ ;
    light_dir.Normalize();
    float NdotL = std::max(collision_normal.Dot(light_dir),0.0f);

    Vec3 viewer_vec = scene.camera_.position_ - ray.collision_point_;
    viewer_vec.Normalize();

    Vec3 reflection_vec = (collision_normal*(2*(light_dir.Dot(collision_normal)))) -
            light_dir;
    reflection_vec.Normalize();

    float RdotV = std::max(viewer_vec.Dot(reflection_vec),0.0f);
    RdotV = pow(RdotV,scene.sphere_.material_.shineness_);

    Vec3 final_color = ambient_result + (diffuse_result*NdotL) + (specular_result*RdotV);
    final_color.x_ = std::min(final_color.x_,1.0f);
    final_color.y_ = std::min(final_color.y_,1.0f);
    final_color.z_ = std::min(final_color.z_,1.0f);
    return final_color;
}

void RayTracer::CastRays()
{    
    GLubyte rgba_texture[height_][width_][4];    
    for(int y=0;y<height_;y++){
        for(int x=0;x<width_;x++){
            float x_coordinate = x - (width_/2.0f);
            float y_coordinate = y - (height_/2.0f);
            Point3 pixel_coordinates = test_scene_.camera_.GetPixelCoordinates(x_coordinate,y_coordinate);
            Vec3 ray_direction = test_scene_.camera_.u_*pixel_coordinates.x_
                    + test_scene_.camera_.v_ * pixel_coordinates.y_
                    - test_scene_.camera_.w_ * test_scene_.camera_.plane_distance_;
            ray_direction.Normalize();
            Ray r(test_scene_.camera_.position_,ray_direction);
            bool collided = test_scene_.TestSphereCollision(r);
            if(collided){
                Vec3 final_color = CalculatePhongLighting(r,test_scene_);
                rgba_texture[y][x][0] = 255*final_color.x_;
                rgba_texture[y][x][1] = 255*final_color.y_;
                rgba_texture[y][x][2] = 255*final_color.z_;
                rgba_texture[y][x][3] = 255;
            }else{
                rgba_texture[y][x][0] = 0;
                rgba_texture[y][x][1] = 0;
                rgba_texture[y][x][2] = 0;
                rgba_texture[y][x][3] = 255;
            }
        }
    }
    gl_renderer_->SetTexture(&rgba_texture[0][0][0]);
}
