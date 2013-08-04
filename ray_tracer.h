#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "gl_context.h"
#include "gl_renderer.h"
#include "gl_widget.h"

#include "scene.h"

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();
    void Initialize();
    void CastRays();
private:    
    GlRenderer *gl_renderer_;
    GlWidget *gl_widget_;
    int width_;
    int height_;
    Scene test_scene_;
};

#endif // RAY_TRACER_H
