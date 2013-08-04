QT += opengl

INCLUDEPATH += /media/vitor/Vitor/Development/Projects/Github/shade-framework  #fix hard coded path
INCLUDEPATH += /home/vitor/glm/glm-0.9.4.3 #fix hard coded path

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
    sphere.cpp

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
    sphere.h

OTHER_FILES += \
    basic.frag \
    basic.vert
