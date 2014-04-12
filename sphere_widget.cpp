#include "sphere_widget.h"
#include "ui_sphere_widget.h"

#include "sphere.h"

SphereWidget::SphereWidget(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::SphereWidget)
{
    ui_->setupUi(this);
}

SphereWidget::~SphereWidget()
{
    delete ui_;
}

void SphereWidget::SetSphere(Sphere *s)
{
    sphere_ = s;
}

void SphereWidget::UpdateValues()
{
    DisconnectAll();
    ui_->name_lineEdit->setText(QString::fromStdString(sphere_->name_));
    ui_->x_doubleSpinBox->setValue(sphere_->position_.x);
    ui_->y_doubleSpinBox->setValue(sphere_->position_.y);
    ui_->z_doubleSpinBox->setValue(sphere_->position_.z);
    ui_->radius_doubleSpinBox->setValue(sphere_->radius_);

    ConnectSlots();
}

void SphereWidget::UpdateSphere()
{

    sphere_->name_ = ui_->name_lineEdit->text().toStdString();
    sphere_->position_.x = ui_->x_doubleSpinBox->value();
    sphere_->position_.y = ui_->y_doubleSpinBox->value();
    sphere_->position_.z = ui_->z_doubleSpinBox->value();
    sphere_->radius_ = ui_->radius_doubleSpinBox->value();
    emit PropertiesChanged();
}

void SphereWidget::ConnectSlots()
{
    QObject::connect(ui_->name_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(UpdateSphere()));
    QObject::connect(ui_->x_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateSphere()));
    QObject::connect(ui_->y_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateSphere()));
    QObject::connect(ui_->z_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateSphere()));
    QObject::connect(ui_->radius_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdateSphere()));
}

void SphereWidget::DisconnectAll()
{
    QObject::disconnect(ui_->name_lineEdit,0,0,0);
    QObject::disconnect(ui_->x_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->y_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->z_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->radius_doubleSpinBox,0,0,0);
}
