#include "gl_widget.h"

#include "gl_renderer.h"

GlWidget::GlWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void GlWidget::initializeGL()
{
    GLContext context;
    context.InitGL();
}

void GlWidget::updateGL()
{
    GlRenderer r;
    r.Render();
}

void GlWidget::resizeGL(int w, int h)
{
}
