#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <GL/glu.h>
#include "mainwindow.h"
#include "showglwidget.h"

ShowGLWidget::ShowGLWidget(QWidget* parent) : QGLWidget(parent)
{
    fullscreen = false;

    obj = new MYOBJECT("F:/experiment/qt/Projects/ComputerAnimatioonTwo/obj.obj");

    ptr = (MainWindow*)parentWidget();

    //m_rtri = 0.0f;
    //m_rquad = 0.0f;

    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    //timer->start(10);
}

ShowGLWidget::~ShowGLWidget()
{
}

void ShowGLWidget::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void ShowGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -250.0f);
    //glRotatef(m_rtri, 0.0f, 0.0f, 1.0f);

    /*for (int i = 0; i < obj->faces.count(); i++) {
        MYFACE fac = obj->faces[i];
        MYPOINT p1 = obj->points[fac.pa];
        MYPOINT p2 = obj->points[fac.pb];
        MYPOINT p3 = obj->points[fac.pc];
        glBegin(GL_TRIANGLES);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(p1.px, p1.py, p1.pz);
            glVertex3f(p2.px, p2.py, p2.pz);
            glVertex3f(p3.px, p3.py, p3.pz);
        glEnd();
    }*/
    for (int i = 0; i < obj->edges.count(); i++) {
        MYEDGE edg = obj->edges[i];
        MYPOINT p1 = obj->points[edg.pi];
        MYPOINT p2 = obj->points[edg.pj];
        glBegin(GL_LINES);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(p1.px, p1.py, p1.pz);
            glVertex3f(p2.px, p2.py, p2.pz);
        glEnd();
    }

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -250.0f);
    //glRotatef(m_rquad, 0.0f, 0.0f, 1.0f);

    for(int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            for (int k = 0; k <= 3; k++) {
                if (ptr->cwidget->buttonClicked[i * 16 + j * 4 + k]) {
                    glPointSize(5.0f);
                }
                else {
                    glPointSize(2.0f);
                }
                glBegin(GL_POINTS);
                    glColor3f(1.0f, 0.0f, 0.0f);
                    glVertex3f(obj->ffd->controlpoints[i][j][k].px, obj->ffd->controlpoints[i][j][k].py, obj->ffd->controlpoints[i][j][k].pz);
                glEnd();
            }
        }
    }

    //m_rtri += 0.5f;
    //m_rquad -= 0.5f;
}

void ShowGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width/(GLfloat)height, 0.1, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ShowGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_F1:
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            showFullScreen(); // can not use key event now!
        }
        else
        {
            showNormal();
        }
        updateGL();
        break;
    case Qt::Key_Escape:
        close();
    }
}
