#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include "gl_context.h"
#include <QGLWidget>

class GlRenderer;

class GlWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GlWidget(QWidget *parent = 0);
    void SetRenderer(GlRenderer*);    
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
signals:
    
public slots:
private:
    GlRenderer* renderer_;
    
};

#endif // GL_WIDGET_H
