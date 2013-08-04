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

void RayTracer::CastRays()
{
    Sphere s(Point3(0,0,0.25),0.1);
    GLubyte rgba_texture[height_][width_][4];
    Point3 viewer(0,0,1);
    float half_width = width_/2;
    float half_height = height_/2;
    for(int y=0;y<height_;y++){
        for(int x=0;x<width_;x++){
            float x_origin = (x - half_width)/half_width;
            float y_origin = (y - half_height)/half_height;
            Point3 current_pixel_pos(x_origin,y_origin,0);
            Vec3 direction = current_pixel_pos - viewer;
            direction.Normalize();
            Ray r(viewer,direction);
            bool collided = s.CheckCollision(r);
            if(collided){
                rgba_texture[y][x][0] = 255;
                rgba_texture[y][x][1] = 0;
                rgba_texture[y][x][2] = 0;
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
