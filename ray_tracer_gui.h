#ifndef RAY_TRACER_GUI_H
#define RAY_TRACER_GUI_H

#include <QMainWindow>

#include "ray_tracer.h"

namespace Ui {
class RayTracerGUI;
}

class RayTracerGUI : public QMainWindow
{
    Q_OBJECT    
public:
    explicit RayTracerGUI(QWidget *parent = 0);
    ~RayTracerGUI();    
private:
    RayTracer ray_tracer_;
    Ui::RayTracerGUI *ui_;
};

#endif // RAY_TRACER_GUI_H
