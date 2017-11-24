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

    QString filename;
    QString FileName;
    QString file_name;
    QString File_Name;
    QLabel *msgLabel;
    void messageINstatusbar();

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void keyPressEvent(QKeyEvent *event);

    ShowGLWidget* swidget;
    ControlWidget* cwidget;

    void toMoveControlPoint();
    void toShowControlPoint();
    void toPlayAnima();
    void toPlayAnimaMore();

private slots:
    void on_action_O_triggered();

    void on_action_S_triggered();

private:
    bool fullscreen;
    bool animaStart;
    int random_number_edge; // from 0 to 11 means 12 edges of the frame
    int makeRandomNumber();
    void WhichMove(int pos, int m, int n);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
