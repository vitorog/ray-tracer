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
    Object* o = ol.Load("../Builds/raytracer-windows-debug/debug/test.obj");
    if(o!=NULL){
        Scene *s = new Scene();
        s->objects_.push_back(o);
        ray_tracer.SetScene(s);
    }
    ray_tracer.Initialize();
    ray_tracer.CastRays();
    return app.exec();
}
