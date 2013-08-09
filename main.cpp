#include <QApplication>
#include <iostream>

#include "ray_tracer_gui.h"

#include "ray_tracer.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    RayTracerGUI gui;
    gui.show();
    return app.exec();
}
