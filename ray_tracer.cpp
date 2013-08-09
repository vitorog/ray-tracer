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


Vec3 CalculatePhongLighting(Ray& r, Scene& scene)
{
    Vec3 ambient_result = scene.sphere_.material_.ambient_
            * scene.light_.material_.ambient_;
    Vec3 diffuse_result = scene.sphere_.material_.diffuse_
            * scene.light_.material_.diffuse_;
    Vec3 specular_result = scene.sphere_.material_.specular_
            * scene.light_.material_.specular_;
    //TODO
    return Vec3(1.0f,0.0f,0.0f);
}

void RayTracer::CastRays()
{    
    GLubyte rgba_texture[height_][width_][4];    
    float half_width = width_/2;
    float half_height = height_/2;
    for(int y=0;y<height_;y++){
        for(int x=0;x<width_;x++){
            float x_origin = (x - half_width)/half_width;
            float y_origin = (y - half_height)/half_height;
            Point3 current_pixel_pos(x_origin,y_origin,0);
            Vec3 direction = current_pixel_pos - test_scene_.camera_.position_;
            direction.Normalize();
            Ray r(test_scene_.camera_.position_,direction);
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
