#include "material_widget.h"
#include "ui_material_widget.h"

#include "material.h"

MaterialWidget::MaterialWidget(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::MaterialWidget)
{
    ui_->setupUi(this);
}

MaterialWidget::~MaterialWidget()
{
    delete ui_;
}

void MaterialWidget::SetMaterial(Material *m)
{
    material_ = m;
}

void MaterialWidget::UpdateValues()
{
    DisconnectAll();
    ui_->ambient_x_spinBox->setValue(material_->ka_.x);
    ui_->ambient_y_spinBox->setValue(material_->ka_.y);
    ui_->ambient_z_spinBox->setValue(material_->ka_.z);

    ui_->diffuse_x_spinBox->setValue(material_->kd_.x);
    ui_->diffuse_y_spinBox->setValue(material_->kd_.y);
    ui_->diffuse_z_spinBox->setValue(material_->kd_.z);

    ui_->specular_x_spinBox->setValue(material_->ks_.x);
    ui_->specular_y_spinBox->setValue(material_->ks_.y);
    ui_->specular_z_spinBox->setValue(material_->ks_.z);
    ConnectSlots();
}

void MaterialWidget::UpdateMaterial()
{
    material_->ka_.x = ui_->ambient_x_spinBox->value();
    material_->ka_.y = ui_->ambient_y_spinBox->value();
    material_->ka_.z = ui_->ambient_z_spinBox->value();

    material_->kd_.x = ui_->diffuse_x_spinBox->value();
    material_->kd_.y = ui_->diffuse_y_spinBox->value();
    material_->kd_.z = ui_->diffuse_z_spinBox->value();

    material_->ks_.x = ui_->diffuse_x_spinBox->value();
    material_->ks_.y = ui_->diffuse_y_spinBox->value();
    material_->ks_.z = ui_->diffuse_z_spinBox->value();
    emit PropertiesChanged();
}

void MaterialWidget::DisconnectAll()
{
    QObject::disconnect(ui_->ambient_x_spinBox,0,0,0);
    QObject::disconnect(ui_->ambient_y_spinBox,0,0,0);
    QObject::disconnect(ui_->ambient_z_spinBox,0,0,0);

    QObject::disconnect(ui_->diffuse_x_spinBox,0,0,0);
    QObject::disconnect(ui_->diffuse_y_spinBox,0,0,0);
    QObject::disconnect(ui_->diffuse_z_spinBox,0,0,0);

    QObject::disconnect(ui_->specular_x_spinBox,0,0,0);
    QObject::disconnect(ui_->specular_y_spinBox,0,0,0);
    QObject::disconnect(ui_->specular_z_spinBox,0,0,0);
}

void MaterialWidget::ConnectSlots()
{
    QObject::connect(ui_->ambient_x_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));
    QObject::connect(ui_->ambient_y_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));
    QObject::connect(ui_->ambient_z_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));

    QObject::connect(ui_->diffuse_x_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));
    QObject::connect(ui_->diffuse_y_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));
    QObject::connect(ui_->diffuse_z_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));

    QObject::connect(ui_->specular_x_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));
    QObject::connect(ui_->specular_y_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));
    QObject::connect(ui_->specular_z_spinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateMaterial()));

}
