#ifndef SPHERE_WIDGET_H
#define SPHERE_WIDGET_H

#include <QWidget>

namespace Ui {
class SphereWidget;
}

class Sphere;

class SphereWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SphereWidget(QWidget *parent = 0);
    ~SphereWidget();
    void SetSphere(Sphere*);

    void UpdateValues();
signals:
    void PropertiesChanged();
private slots:
    void UpdateSphere();
private:    
    void ConnectSlots();
    void DisconnectAll();
    Ui::SphereWidget *ui_;
    Sphere* sphere_;
};

#endif // SPHERE_WIDGET_H
