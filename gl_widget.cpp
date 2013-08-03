#include "gl_widget.h"

#include "gl_renderer.h"

GlWidget::GlWidget(QWidget *parent) :    
    QGLWidget(parent),
    renderer_(NULL)
{    
}

void GlWidget::SetRenderer(GlRenderer *r)
{
    renderer_ = r;
}

void GlWidget::initializeGL()
{
    if(renderer_ != NULL){
        renderer_->Initialize();
    }
}

void GlWidget::paintGL()
{
    if(renderer_ != NULL){
        renderer_->Render();
    }
}

void GlWidget::resizeGL(int w, int h)
{
    if(renderer_ != NULL){
        renderer_->Resize(w,h);
    }
}
