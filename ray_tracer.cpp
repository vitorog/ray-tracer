#include "ray_tracer.h"

#include <cmath>

RayTracer::RayTracer()
    : gl_renderer_(NULL),
      gl_widget_(NULL),
      width_(640),
      height_(480)
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

void RayTracer::CastRays()
{
    GLubyte rgba_texture[height_][width_][4];
    for(int y=0;y<height_;y++){
        for(int x=0;x<width_;x++){
            rgba_texture[y][x][0] = 255;
            rgba_texture[y][x][1] = 0;
            rgba_texture[y][x][2] = 0;
            rgba_texture[y][x][3] = 255;
        }
    }
    gl_renderer_->SetTexture(&rgba_texture[0][0][0]);
}
