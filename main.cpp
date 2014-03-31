#include <QApplication>
#include <iostream>
#include <scene.h>
#include <obj_loader.h>

#include "ray_tracer.h"

int main(int argc, char** argv)
{
//    QApplication app(argc,argv);
//    RayTracerGUI gui;
//    gui.show();
//    return app.exec();

    QApplication app(argc,argv);
    RayTracer ray_tracer;

    OBJLoader ol;
    std::vector<Object*> objs  = ol.Load("untitled2.obj");
    if(!objs.empty()){
        Scene *s = new Scene();
        for(int i = 0; i < objs.size(); i++){
            s->objects_.push_back(objs.at(i));
        }
        Camera *c = new Camera(glm::vec3(0.0f,0.0f,20.0f),
                               glm::vec3(0.0f,0.0f,-1.0f),
                               glm::vec3(0.0f,1.0f,0.0f));
        Material m;
        m.ka_ = glm::vec3(0.3,0.3,0.3);
        m.kd_ = glm::vec3(0.5,0.5,0.5);
        m.ks_ = glm::vec3(0.8,0.8,0.8);
        m.ns_ = 1.0f;
        m.tr_ = 0.0f;
        PointLight *l = new PointLight(glm::vec3(0.0f,0.0f,10.0f),m);
        s->light_ = l;
        s->camera_ = c;
        ray_tracer.SetScene(s);
    }
    ray_tracer.Initialize();
    ray_tracer.CastRays();
    return app.exec();
}
