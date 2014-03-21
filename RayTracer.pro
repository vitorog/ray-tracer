QT += opengl

INCLUDEPATH += ../shade-framework
INCLUDEPATH += ../../../glm-0.9.5.2/glm

LIBS += -lGLEW

SOURCES += \
    main.cpp \    
    gl_widget.cpp \
    gl_renderer.cpp \
    ray_tracer.cpp \
    ray.cpp \
    scene.cpp \   
    sphere.cpp \    
    camera.cpp \
    light.cpp \
    ray_tracer_gui.cpp \
    object.cpp

HEADERS += \   
    gl_widget.h \
    gl_renderer.h \
    ray_tracer.h \
    ray.h \
    scene.h \    
    sphere.h \    
    camera.h \
    light.h \
    ray_tracer_gui.h \
    object.h

OTHER_FILES += \
    basic.frag \
    basic.vert

FORMS += \
    ray_tracer_gui.ui


unix:!macx: LIBS += -L$$PWD/../Builds/shade-framework-build/ -lshade-framework

INCLUDEPATH += $$PWD/../Builds/shade-framework-build
DEPENDPATH += $$PWD/../Builds/shade-framework-build
