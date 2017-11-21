#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QMouseEvent>
#include <QWheelEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    swidget = new ShowGLWidget(this);
    cwidget = new ControlWidget(this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(swidget);
    layout->addWidget(cwidget);
    layout->setStretchFactor(swidget, 10);
    layout->setStretchFactor(cwidget, 1);
    widget->setLayout(layout);

    connect(cwidget->sliderx, &QSlider::sliderReleased, this, &MainWindow::toMoveControlPoint);
    connect(cwidget->slidery, &QSlider::sliderReleased, this, &MainWindow::toMoveControlPoint);
    connect(cwidget->sliderz, &QSlider::sliderReleased, this, &MainWindow::toMoveControlPoint);
    for (int i = 0; i < 64; i++) {
        connect(cwidget->controlbutton[i], &QPushButton::clicked, this, &MainWindow::toShowControlPoint);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toMoveControlPoint()
{
    QFile f("F:\\experiment\\qt\\Projects\\ComputerAnimatioonTwo\\ObjCalculateRight.txt");
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream txtOutput(&f);

    QString sliderName = sender()->objectName();
    for(int i = 0; i < 64; i++) {
        if (cwidget->buttonClicked[i]) {
            int ti = i / 16;
            int tj = (i - (ti * 16)) / 4;
            int tk = (i - (ti * 16)) - (tj * 4);
            if (sliderName.compare("xSlider") == 0) {
                swidget->obj->ffd->controlpoints[ti][tj][tk].px += cwidget->sliderx->value();
                // qDebug() << "x" << swidget->obj->ffd->controlpoints[ti][tj][tk].px;
            }
            else if (sliderName.compare("ySlider") == 0) {
                swidget->obj->ffd->controlpoints[ti][tj][tk].py += cwidget->slidery->value();
                // qDebug() << "y" << swidget->obj->ffd->controlpoints[ti][tj][tk].py;
            }
            else {
                swidget->obj->ffd->controlpoints[ti][tj][tk].pz += cwidget->sliderz->value();
                // qDebug() << "z" << swidget->obj->ffd->controlpoints[ti][tj][tk].pz;
            }
            // qDebug() << ti << tj << tk;
        }
    }
    for (int i = 0; i < swidget->obj->points.size(); i++) {
        swidget->obj->points[i] = swidget->obj->ffd->calculateBezier(swidget->obj->normalizedpoints[i]);
        txtOutput << swidget->obj->points[i].px << swidget->obj->points[i].py << swidget->obj->points[i].pz << endl;
    }

    cwidget->sliderx->setValue(0);
    cwidget->slidery->setValue(0);
    cwidget->sliderz->setValue(0);
    swidget->updateGL();

    f.close();
}

void MainWindow::toShowControlPoint()
{
    swidget->updateGL();
}

/*void MainWindow::mousePressEvent(QMouseEvent *e)
{
    mwidget->manager->getInitPos(e->x(),e->y());
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::MiddleButton)
    {
        if(e->modifiers()==Qt::CTRL)
        {
            mwidget->manager->executeTranslateOperation(e->x(),e->y());
        }
        else
        {
            mwidget->manager->executeRotateOperation(e->x(),e->y());
        }
    }
    mwidget->updateGL();
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if(e->delta()>=0)
    {
        mwidget->manager->executeScaleOperation(-0.1);
    }else
    {
        mwidget->manager->executeScaleOperation(0.1);
    }
    mwidget->updateGL();
}*/
