#include "ray_tracer_gui.h"
#include "ui_ray_tracer_gui.h"

#include <QLayout>

RayTracerGUI::RayTracerGUI(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::RayTracerGUI)
{
    ui_->setupUi(this);

    ray_tracer_.Initialize();
    ray_tracer_.CastRays();
//    ui_->gl_widget_frame->layout()->addWidget(ray_tracer_.gl_widget_);
}

RayTracerGUI::~RayTracerGUI()
{
    delete ui_;
}
