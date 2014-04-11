#include "material_widget.h"
#include "ui_material_widget.h"

MaterialWidget::MaterialWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialWidget)
{
    ui->setupUi(this);
}

MaterialWidget::~MaterialWidget()
{
    delete ui;
}
