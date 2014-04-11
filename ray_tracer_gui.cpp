#include "ray_tracer_gui.h"
#include "ui_ray_tracer_gui.h"

#include <QLayout>

#include "sphere.h"
#include "plane.h"

RayTracerGUI::RayTracerGUI(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::RayTracerGUI)
{
    ui_->setupUi(this);

    //    ray_tracer_.Initialize();
    //    ray_tracer_.CastRays();

    QObject::connect(ui_->add_sphere_pushButton,SIGNAL(clicked()),this,SLOT(AddSphere()));
    QObject::connect(ui_->add_plane_pushButton,SIGNAL(clicked()),this,SLOT(AddPlane()));
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

void RayTracerGUI::AddSphere()
{
    RayTracerObject* sphere = new Sphere(glm::vec3(0.0f,0.0f,-1.0f),0.5f);
    sphere->material_->kd_ = glm::vec3(0.8f,0.1f,0.1f);
    sphere->material_->illum_ = 3;
    sphere->name_ = "Sphere";
    scene_->objects_.push_back(sphere);
    QTreeWidgetItem* object_tree_item = new QTreeWidgetItem();
    object_tree_item->setText(0,QString::fromStdString(sphere->name_));
    ui_->objects_treeWidget->insertTopLevelItem(0,object_tree_item);
    Update();
}

void RayTracerGUI::AddPlane()
{
    RayTracerObject* plane = new Plane(glm::vec3(0.0f,-2.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
    plane->material_->kd_ = glm::vec3(0.2f,0.8f,0.2f);
    plane->material_->illum_ = 3;
    plane->name_ = "Plane";
    scene_->objects_.push_back(plane);
    QTreeWidgetItem* object_tree_item = new QTreeWidgetItem();
    object_tree_item->setText(0,QString::fromStdString(plane->name_));
    ui_->objects_treeWidget->insertTopLevelItem(0,object_tree_item);
    Update();
}

void RayTracerGUI::Update()
{
    ray_tracer_.CastRays();
}
