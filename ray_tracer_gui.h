#ifndef RAY_TRACER_GUI_H
#define RAY_TRACER_GUI_H

#include <QMainWindow>

#include "ray_tracer.h"

class SphereWidget;
class PlaneWidget;
class MaterialWidget;

namespace Ui {
class RayTracerGUI;
}

class RayTracerGUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit RayTracerGUI(QWidget *parent = 0);
    ~RayTracerGUI();
private slots:
    void OnAddSphere();
    void OnAddPlane();
    void OnSelectionChange();
    void Update();
private:        
    RayTracer ray_tracer_;
    RayTracerScene* scene_;
    Ui::RayTracerGUI *ui_;
    SphereWidget *sphere_widget_;
    PlaneWidget *plane_widget_;
    MaterialWidget *material_widget_;
};

#endif // RAY_TRACER_GUI_H
