#ifndef SHOWGLWIDGET_H
#define SHOWGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include "mypoint.h"
#include "myedge.h"
#include "myface.h"
#include "myobject.h"
#include "ffd.h"

class ShowGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    ShowGLWidget(QWidget* parent = 0);
    ~ShowGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *event); // handle press key event

private:
    bool fullscreen;
    GLfloat m_rtri;                                 //控制三角形的角度
    GLfloat m_rquad;                                //控制四边形的角度
};

#endif // SHOWGLWIDGET_H
