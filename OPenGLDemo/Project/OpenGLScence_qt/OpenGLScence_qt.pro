#-------------------------------------------------
#
# Project created by QtCreator 2016-03-05T11:15:04
#
#-------------------------------------------------

QT       += opengl core gui
LIBS+= -L ../../lib/lib_qt -lglew32 -lglut32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLScence_qt
TEMPLATE = app

INCLUDEPATH += ../../include

SOURCES += main.cpp\
        widget.cpp\
       GLMainWidget.cpp \
    RoamingScenceManager.cpp \
    ../../src/MathAPIKernel_Qt/Matrix4D.cpp \
    ../../src/MathAPIKernel_Qt/Position3D.cpp \
    ../../src/MathAPIKernel_Qt/Vector3D.cpp

HEADERS  += widget.h\
 GLMainWidget.h \
    RoamingScenceManager.h \
    ../../include/MathAPIKernel/Matrix4D.h \
    ../../include/MathAPIKernel/Position3D.h \
    ../../include/MathAPIKernel/Vector3D.h
