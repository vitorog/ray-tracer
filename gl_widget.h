#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include "gl_context.h"

#include <QGLWidget>

class GlWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GlWidget(QWidget *parent = 0);
protected:
    void initializeGL();
    void updateGL();
    void resizeGL(int w, int h);
signals:
    
public slots:
    
};

#endif // GL_WIDGET_H
