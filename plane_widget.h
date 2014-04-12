#ifndef PLANE_WIDGET_H
#define PLANE_WIDGET_H

#include <QWidget>

namespace Ui {
class PlaneWidget;
}

class Plane;

class PlaneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlaneWidget(QWidget *parent = 0);
    ~PlaneWidget();
    void SetPlane(Plane*);
    void UpdateValues();
signals:
    void PropertiesChanged();
private slots:
    void UpdatePlane();
private:
    void DisconnectAll();
    void ConnectSlots();
    Ui::PlaneWidget *ui_;
    Plane* plane_;
};

#endif // PLANE_WIDGET_H
