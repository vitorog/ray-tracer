#include "plane_widget.h"
#include "ui_plane_widget.h"

#include "plane.h"

PlaneWidget::PlaneWidget(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::PlaneWidget)
{
    ui_->setupUi(this);
}

PlaneWidget::~PlaneWidget()
{
    delete ui_;
}

void PlaneWidget::SetPlane(Plane *p)
{
    plane_ = p;
}

void PlaneWidget::UpdateValues()
{
    DisconnectAll();
    ui_->name_lineEdit->setText(QString::fromStdString(plane_->name_));
    ui_->x_doubleSpinBox->setValue(plane_->position_.x);
    ui_->y_doubleSpinBox->setValue(plane_->position_.y);
    ui_->z_doubleSpinBox->setValue(plane_->position_.z);

    ui_->nx_doubleSpinBox->setValue(plane_->normal_.x);
    ui_->ny_doubleSpinBox->setValue(plane_->normal_.y);
    ui_->nz_doubleSpinBox->setValue(plane_->normal_.z);
    ConnectSlots();
}

void PlaneWidget::UpdatePlane()
{
    plane_->name_ = ui_->name_lineEdit->text().toStdString();
    plane_->position_.x = ui_->x_doubleSpinBox->value();
    plane_->position_.y = ui_->y_doubleSpinBox->value();
    plane_->position_.z = ui_->z_doubleSpinBox->value();
    plane_->normal_.x = ui_->nx_doubleSpinBox->value();
    plane_->normal_.y = ui_->ny_doubleSpinBox->value();
    plane_->normal_.z = ui_->nz_doubleSpinBox->value();
    emit PropertiesChanged();
}

void PlaneWidget::ConnectSlots()
{
    QObject::connect(ui_->name_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(UpdatePlane()));
    QObject::connect(ui_->x_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdatePlane()));
    QObject::connect(ui_->y_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdatePlane()));
    QObject::connect(ui_->z_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdatePlane()));
    QObject::connect(ui_->nx_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdatePlane()));
    QObject::connect(ui_->ny_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdatePlane()));
    QObject::connect(ui_->nz_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpdatePlane()));
}

void PlaneWidget::DisconnectAll()
{
    QObject::disconnect(ui_->name_lineEdit,0,0,0);
    QObject::disconnect(ui_->x_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->y_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->z_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->nx_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->ny_doubleSpinBox,0,0,0);
    QObject::disconnect(ui_->nz_doubleSpinBox,0,0,0);
}
