#include "ray_tracer_gui.h"
#include "ui_ray_tracer_gui.h"

#include <QLayout>

#include "sphere.h"
#include "plane.h"

#include "sphere_widget.h"
#include "plane_widget.h"
#include "material_widget.h"

RayTracerGUI::RayTracerGUI(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::RayTracerGUI)
{
    ui_->setupUi(this);

    sphere_widget_ = new SphereWidget();
    QObject::connect(sphere_widget_,SIGNAL(PropertiesChanged()),this,SLOT(Update()));
    material_widget_ = new MaterialWidget();
    QObject::connect(material_widget_,SIGNAL(PropertiesChanged()),this,SLOT(Update()));
    plane_widget_ = new PlaneWidget();
    QObject::connect(plane_widget_,SIGNAL(PropertiesChanged()),this,SLOT(Update()));

    ui_->properties_frame->layout()->addWidget(sphere_widget_);
    ui_->properties_frame->layout()->addWidget(plane_widget_);
    ui_->properties_frame->layout()->addWidget(material_widget_);    

    //    ray_tracer_.Initialize();
    //    ray_tracer_.CastRays();

    QObject::connect(ui_->add_sphere_pushButton,SIGNAL(clicked()),this,SLOT(OnAddSphere()));
    QObject::connect(ui_->add_plane_pushButton,SIGNAL(clicked()),this,SLOT(OnAddPlane()));
    QObject::connect(ui_->objects_treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(OnSelectionChange()));
    scene_ = new RayTracerScene();
    Camera *c = new Camera(glm::vec3(0.0f,0.0f,1.0f),
                           glm::vec3(0.0f,0.0f,-1.0f),
                           glm::vec3(0.0f,1.0f,0.0f));
    Material m;
    m.ka_ = glm::vec3(0.1,0.1,0.1);
    m.kd_ = glm::vec3(1.0,1.0,1.0);
    m.ks_ = glm::vec3(0.2,0.2,0.2);
    PointLight *l = new PointLight(glm::vec3(1.0f,1.0f,2.0f),m);
    scene_->light_ = l;
    scene_->camera_ = c;

    ray_tracer_.Initialize();
    ray_tracer_.SetScene(scene_);
    ui_->gl_widget_frame->layout()->addWidget(ray_tracer_.GetWidget());
    Update();
}

RayTracerGUI::~RayTracerGUI()
{
    delete ui_;
}

void RayTracerGUI::OnAddSphere()
{
    RayTracerObject* sphere = new Sphere(glm::vec3(0.0f,0.0f,-1.0f),0.5f);
    sphere->material_->kd_ = glm::vec3(0.8f,0.1f,0.1f);
    sphere->material_->illum_ = 3;
    sphere->name_ = "Sphere";
    scene_->objects_.push_back(sphere);
    QTreeWidgetItem* object_tree_item = new QTreeWidgetItem();
    object_tree_item->setText(0,QString::fromStdString(sphere->name_));
    ui_->objects_treeWidget->insertTopLevelItem(scene_->objects_.size()-1,object_tree_item);
    Update();
}

void RayTracerGUI::OnAddPlane()
{
    RayTracerObject* plane = new Plane(glm::vec3(0.0f,-2.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
    plane->material_->kd_ = glm::vec3(0.2f,0.8f,0.2f);
    plane->material_->illum_ = 3;
    plane->name_ = "Plane";
    scene_->objects_.push_back(plane);
    QTreeWidgetItem* object_tree_item = new QTreeWidgetItem();
    object_tree_item->setText(0,QString::fromStdString(plane->name_));
    ui_->objects_treeWidget->insertTopLevelItem(scene_->objects_.size()-1,object_tree_item);
    Update();
}

void RayTracerGUI::OnSelectionChange()
{
    sphere_widget_->hide();
    plane_widget_->hide();
    material_widget_->hide();

    int current_index = ui_->objects_treeWidget->indexOfTopLevelItem(ui_->objects_treeWidget->currentItem());
    RayTracerObject *obj = scene_->objects_.at(current_index);
    Sphere *s = dynamic_cast<Sphere*>(obj);
    if(s != NULL){
        sphere_widget_->show();
        sphere_widget_->SetSphere(s);
        sphere_widget_->UpdateValues();
        material_widget_->show();
        material_widget_->SetMaterial(s->material_);
        material_widget_->UpdateValues();
        return;
    }

    Plane *p = dynamic_cast<Plane*>(obj);
    if(p != NULL){
        plane_widget_->show();
        plane_widget_->SetPlane(p);
        plane_widget_->UpdateValues();
        material_widget_->show();
        material_widget_->SetMaterial(p->material_);
        material_widget_->UpdateValues();
        return;
    }
}

void RayTracerGUI::Update()
{
    ray_tracer_.CastRays();
}
