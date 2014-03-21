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
    glm::vec3 CastRay(Point3 origin, Vec3 direction, int depth);
    bool CastShadowRay(Point3 origin, Vec3 direction);
    GlWidget *gl_widget_;
    Scene test_scene_;
private:    
    GlRenderer *gl_renderer_;
    int width_;
    int height_;
    int max_depth_;
};

#endif // RAY_TRACER_H
