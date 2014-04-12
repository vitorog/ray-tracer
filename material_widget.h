#ifndef MATERIAL_WIDGET_H
#define MATERIAL_WIDGET_H

#include <QWidget>

namespace Ui {
class MaterialWidget;
}

class Material;

class MaterialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialWidget(QWidget *parent = 0);
    ~MaterialWidget();
    void SetMaterial(Material*);
    void UpdateValues();
private slots:
    void UpdateMaterial();
signals:
    void PropertiesChanged();
private:
    void DisconnectAll();
    void ConnectSlots();
    Ui::MaterialWidget *ui_;
    Material* material_;
};

#endif // MATERIAL_WIDGET_H
