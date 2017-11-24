#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QFileInfo>
#include <GL/glu.h>
#include "mainwindow.h"
#include "showglwidget.h"

ShowGLWidget::ShowGLWidget(QWidget* parent) : QGLWidget(parent)
{
    /*filename = QFileDialog::getOpenFileName(this, "Open An Object", QDir::currentPath(), "Object files(*.obj);;All files(*.*)");
    if (!filename.isNull()) { //用户选择了文件
    }
    else { // 用户取消选择
       filename = "F:/experiment/qt/Projects/ComputerAnimatioonTwo/obj.obj";
    }
    QFileInfo fileinfo = QFileInfo(filename);
    file_name = fileinfo.fileName();
    obj = new MYOBJECT(filename);*/
    ptr = (MainWindow*)parentWidget();
    this->setFocusPolicy(Qt::StrongFocus);
    manager=new RoamingScenceManager();
    ShowFrame = true;
}

ShowGLWidget::~ShowGLWidget()
{
}

void ShowGLWidget::initializeGL()
{
    manager->init();
    /*glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);*/
}

void ShowGLWidget::paintGL()
{
    manager->render();
    if (!obj) return; // make sure something is imported now

    //glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, -250.0f);
    //glRotatef(m_rtri, 0.0f, 0.0f, 1.0f);

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

    if (ShowFrame) {
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
                    qDebug() << "Why!";
                }
            }
        }
        DrawFrame();
    }
}

bool ShowGLWidget::counter(int i, int j, int k)
{
    int count = 0;
    if(i == 0 || i == 3) count++;
    if(j == 0 || j == 3) count++;
    if(k == 0 || k == 3) count++;
    if (count > 1) return true;
    else return false;
}

void ShowGLWidget::DrawFrame()
{
    int x;
    for(int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            for (int k = 0; k <= 3; k++) {
                x = i + 1;
                if (x != 4) {
                    if (counter(i, j, k) && counter(x, j, k)) {
                        glBegin(GL_LINES);
                            glColor3f(1.0f, 0.0f, 0.0f);
                            glVertex3f(obj->ffd->controlpoints[i][j][k].px,
                                       obj->ffd->controlpoints[i][j][k].py,
                                       obj->ffd->controlpoints[i][j][k].pz);
                            glVertex3f(obj->ffd->controlpoints[x][j][k].px,
                                       obj->ffd->controlpoints[x][j][k].py,
                                       obj->ffd->controlpoints[x][j][k].pz);
                        glEnd();
                    }
                }
                x = i - 1;
                if (x != -1) {
                    if (counter(i, j, k) && counter(x, j, k)) {
                        glBegin(GL_LINES);
                            glColor3f(1.0f, 0.0f, 0.0f);
                            glVertex3f(obj->ffd->controlpoints[i][j][k].px,
                                       obj->ffd->controlpoints[i][j][k].py,
                                       obj->ffd->controlpoints[i][j][k].pz);
                            glVertex3f(obj->ffd->controlpoints[x][j][k].px,
                                       obj->ffd->controlpoints[x][j][k].py,
                                       obj->ffd->controlpoints[x][j][k].pz);
                        glEnd();
                    }
                }
                x = j + 1;
                if (x != 4) {
                    if (counter(i, j, k) && counter(i, x, k)) {
                        glBegin(GL_LINES);
                            glColor3f(1.0f, 0.0f, 0.0f);
                            glVertex3f(obj->ffd->controlpoints[i][j][k].px,
                                       obj->ffd->controlpoints[i][j][k].py,
                                       obj->ffd->controlpoints[i][j][k].pz);
                            glVertex3f(obj->ffd->controlpoints[i][x][k].px,
                                       obj->ffd->controlpoints[i][x][k].py,
                                       obj->ffd->controlpoints[i][x][k].pz);
                        glEnd();
                    }
                }
                x = j - 1;
                if (x != -1) {
                    if (counter(i, j, k) && counter(i, x, k)) {
                        glBegin(GL_LINES);
                            glColor3f(1.0f, 0.0f, 0.0f);
                            glVertex3f(obj->ffd->controlpoints[i][j][k].px,
                                       obj->ffd->controlpoints[i][j][k].py,
                                       obj->ffd->controlpoints[i][j][k].pz);
                            glVertex3f(obj->ffd->controlpoints[i][x][k].px,
                                       obj->ffd->controlpoints[i][x][k].py,
                                       obj->ffd->controlpoints[i][x][k].pz);
                        glEnd();
                    }
                }
                x = k + 1;
                if (x != 4) {
                    if (counter(i, j, k) && counter(i, j, x)) {
                        glBegin(GL_LINES);
                            glColor3f(1.0f, 0.0f, 0.0f);
                            glVertex3f(obj->ffd->controlpoints[i][j][k].px,
                                       obj->ffd->controlpoints[i][j][k].py,
                                       obj->ffd->controlpoints[i][j][k].pz);
                            glVertex3f(obj->ffd->controlpoints[i][j][x].px,
                                       obj->ffd->controlpoints[i][j][x].py,
                                       obj->ffd->controlpoints[i][j][x].pz);
                        glEnd();
                    }
                }
                x = k - 1;
                if (x != -1) {
                    if (counter(i, j, k) && counter(i, j, x)) {
                        glBegin(GL_LINES);
                            glColor3f(1.0f, 0.0f, 0.0f);
                            glVertex3f(obj->ffd->controlpoints[i][j][k].px,
                                       obj->ffd->controlpoints[i][j][k].py,
                                       obj->ffd->controlpoints[i][j][k].pz);
                            glVertex3f(obj->ffd->controlpoints[i][j][x].px,
                                       obj->ffd->controlpoints[i][j][x].py,
                                       obj->ffd->controlpoints[i][j][x].pz);
                        glEnd();
                    }
                }
            }
        }
    }
}

void ShowGLWidget::resizeGL(int width, int height)
{
    /*glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width/(GLfloat)height, 0.1, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/
    glViewport(0,-(width-height)/2,width,width);
}
