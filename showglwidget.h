#ifndef SHOWGLWIDGET_H
#define SHOWGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include "mypoint.h"
#include "myedge.h"
#include "myface.h"
#include "myobject.h"
#include "ffd.h"
#include "OPenGLDemo/Project/OpenGLScence_qt/RoamingScenceManager.h"

class MainWindow;
class ShowGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    ShowGLWidget(QWidget* parent = 0);
    ~ShowGLWidget();

    QString filename;
    QString file_name;
    MYOBJECT* obj;
    MainWindow* ptr;
    bool ShowFrame;

    RoamingScenceManager* manager;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    bool counter(int i, int j, int k);
    void DrawFrame();

private:
};

#endif // SHOWGLWIDGET_H
