#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include "showglwidget.h"
#include "controlwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ShowGLWidget* swidget;
    ControlWidget* cwidget;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
