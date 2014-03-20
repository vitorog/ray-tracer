#include <QApplication>
#include <iostream>



#include "ray_tracer.h"

int main(int argc, char** argv)
{
//    QApplication app(argc,argv);
//    RayTracerGUI gui;
//    gui.show();
//    return app.exec();

    QApplication app(argc,argv);
    RayTracer ray_tracer;
    ray_tracer.Initialize();
    ray_tracer.CastRays();
    return app.exec();
}
