#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
class RoamingScenceManager;
class GLMainWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLMainWidget(QWidget *parent = 0);
    ~GLMainWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void wheelEvent(QWheelEvent *e);

private:
    RoamingScenceManager*manager;
};

#endif // GLWIDGET_H
