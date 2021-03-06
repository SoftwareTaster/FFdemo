#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T14:26:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl

TARGET = ComputerAnimatioonTwo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    showglwidget.cpp \
    myedge.cpp \
    mypoint.cpp \
    myface.cpp \
    myobject.cpp \
    ffd.cpp \
    controlwidget.cpp \
    OPenGLDemo/Project/OpenGLScence_qt/RoamingScenceManager.cpp \
    OPenGLDemo/src/MathAPIKernel_Qt/Matrix4D.cpp \
    OPenGLDemo/src/MathAPIKernel_Qt/Position3D.cpp \
    OPenGLDemo/src/MathAPIKernel_Qt/Vector3D.cpp

HEADERS += \
        mainwindow.h \
    showglwidget.h \
    myedge.h \
    mypoint.h \
    myface.h \
    myobject.h \
    ffd.h \
    controlwidget.h \
    OPenGLDemo/Project/OpenGLScence_qt/RoamingScenceManager.h \
    OPenGLDemo/include/MathAPIKernel/Matrix4D.h \
    OPenGLDemo/include/MathAPIKernel/Position3D.h \
    OPenGLDemo/include/MathAPIKernel/Vector3D.h

FORMS += \
        mainwindow.ui

win32:LIBS += -lOpengl32 \
                -lglu32 \
                -lglut

win32:LIBS+= -L$$PWD/OPenGLDemo/lib/lib_qt/ -lglew32
win32:LIBS+= -L$$PWD/OPenGLDemo/lib/lib_qt/ -lglut32
