QT += opengl

INCLUDEPATH += ../shade-framework
INCLUDEPATH += ../../../glm-0.9.5.2/glm

LIBS += -lGLEW

SOURCES += \
    main.cpp \
    ../shade-framework/gl_context.cpp \
    ../shade-framework/shader_program.cpp \
    gl_widget.cpp \
    gl_renderer.cpp \
    ray_tracer.cpp \
    ray.cpp \
    scene.cpp \
    ../shade-framework/vec3.cpp \
    ../shade-framework/point3.cpp \
    sphere.cpp \
    material.cpp \
    camera.cpp \
    light.cpp \
    ray_tracer_gui.cpp \
    object.cpp

HEADERS += \
    ../shade-framework/debug.h \
    ../shade-framework/gl_context.h \
    ../shade-framework/shader_program.h \
    gl_widget.h \
    gl_renderer.h \
    ray_tracer.h \
    ray.h \
    scene.h \
    ../shade-framework/vec3.h \
    ../shade-framework/point3.h \
    sphere.h \
    material.h \
    camera.h \
    light.h \
    ray_tracer_gui.h \
    object.h

OTHER_FILES += \
    basic.frag \
    basic.vert

FORMS += \
    ray_tracer_gui.ui
