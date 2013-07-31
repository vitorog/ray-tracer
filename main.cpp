#include <QApplication>
#include <iostream>


#include "gl_context.h"
#include "gl_widget.h"


int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    GlWidget gl_widget;
    gl_widget.show();
    return app.exec();
}
