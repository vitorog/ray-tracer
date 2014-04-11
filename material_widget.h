#ifndef MATERIAL_WIDGET_H
#define MATERIAL_WIDGET_H

#include <QWidget>

namespace Ui {
class MaterialWidget;
}

class MaterialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialWidget(QWidget *parent = 0);
    ~MaterialWidget();

private:
    Ui::MaterialWidget *ui;
};

#endif // MATERIAL_WIDGET_H
