QT += opengl

INCLUDEPATH += ../shade-framework
INCLUDEPATH += ../../../Libs/glm-0.9.5.2/glm

SOURCES += \
    main.cpp \    
    gl_widget.cpp \
    gl_renderer.cpp \
    ray_tracer.cpp \
    ray.cpp \    
    ray_tracer_gui.cpp \    

HEADERS += \   
    gl_widget.h \
    gl_renderer.h \
    ray_tracer.h \
    ray.h \    
    ray_tracer_gui.h \    

OTHER_FILES += \
    basic.frag \
    basic.vert

FORMS += \
    ray_tracer_gui.ui


unix:!macx: LIBS += -L$$PWD/../Builds/shade-framework-build/ -lshade-framework
unix: LIBS += -lGLEW

INCLUDEPATH += $$PWD/../Builds/shade-framework-build
DEPENDPATH += $$PWD/../Builds/shade-framework-build

win32: LIBS += -L$$PWD/../../../Libs/glew-1.10.0_mingw/lib/ -llibglew32

INCLUDEPATH += $$PWD/../../../Libs/glew-1.10.0_mingw/include
DEPENDPATH += $$PWD/../../../Libs/glew-1.10.0_mingw/include


win32: LIBS += -L$$PWD/../Builds/shade-framework-build/ -llibshade-framework
