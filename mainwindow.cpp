#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
#include <QTimer>
#include <OPenGLDemo/include/MathAPIKernel/Vector3D.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fullscreen = false;
    animaStart = false;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::toPlayAnimaMore);
    timer->start(5);

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

    // move control points and other points when move sliders
    connect(cwidget->sliderx, &QSlider::sliderReleased, this, &MainWindow::toMoveControlPoint);
    connect(cwidget->slidery, &QSlider::sliderReleased, this, &MainWindow::toMoveControlPoint);
    connect(cwidget->sliderz, &QSlider::sliderReleased, this, &MainWindow::toMoveControlPoint);
    // play animation when click play button
    connect(cwidget->playButton, &QPushButton::clicked, this, &MainWindow::toPlayAnima);
    // emphasize the points and buttons when being chosen
    for (int i = 0; i < 64; i++) {
        connect(cwidget->controlbutton[i], &QPushButton::clicked, this, &MainWindow::toShowControlPoint);
    }

    msgLabel = new QLabel;
    msgLabel->setMinimumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addWidget(msgLabel);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    messageINstatusbar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::messageINstatusbar()
{
    QString tmpstr = "";
    tmpstr+=QString("T:%1,%2,%3\t\t").arg(swidget->manager->TempTranslateVec->X())
            .arg(swidget->manager->TempTranslateVec->Y())
            .arg(swidget->manager->TempTranslateVec->Z());
    tmpstr+=QString("S:%1\t\t").arg(swidget->manager->TempscaleFactor);
    tmpstr+=QString("Ea:%1,%2,%3\tEb:%4,%5,%6")
            .arg(swidget->manager->NewEye->X()).arg(swidget->manager->NewEye->Y()).arg(swidget->manager->NewEye->Z())
            .arg(swidget->manager->NewUp->X()).arg(swidget->manager->NewUp->Y()).arg(swidget->manager->NewUp->Z());
    msgLabel->setText(tmpstr);
}

void MainWindow::toMoveControlPoint()
{
    //QFile f("F:\\experiment\\qt\\Projects\\ComputerAnimatioonTwo\\ObjCalculateRight.txt");
    //f.open(QIODevice::WriteOnly | QIODevice::Text);
    //QTextStream txtOutput(&f);

    if (!swidget->obj) return;

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
        //txtOutput << swidget->obj->points[i].px << swidget->obj->points[i].py << swidget->obj->points[i].pz << endl;
    }

    cwidget->sliderx->setValue(0);
    cwidget->slidery->setValue(0);
    cwidget->sliderz->setValue(0);
    swidget->updateGL();

    //f.close();
}

void MainWindow::toShowControlPoint()
{
    swidget->updateGL();
}

void MainWindow::toPlayAnima()
{
    if (!swidget->obj) return; // make sure it works when obj is not loaded
    animaStart = !animaStart;

    if (animaStart) {
        swidget->ShowFrame = false;
    }
    else {
        swidget->ShowFrame = true;
    }
    swidget->updateGL();
}

void MainWindow::toPlayAnimaMore()
{
    if (animaStart) {
        random_number_edge = makeRandomNumber();
        switch (random_number_edge) {
        case 0:
            WhichMove(0, 0, 0);
            break;
        case 1:
            WhichMove(0, 0, 3);
            break;
        case 2:
            WhichMove(0, 3, 0);
            break;
        case 3:
            WhichMove(0, 3, 3);
            break;
        case 4:
            WhichMove(1, 0, 0);
            break;
        case 5:
            WhichMove(1, 0, 3);
            break;
        case 6:
            WhichMove(1, 3, 0);
            break;
        case 7:
            WhichMove(1, 3, 3);
            break;
        case 8:
            WhichMove(2, 0, 0);
            break;
        case 9:
            WhichMove(2, 0, 3);
            break;
        case 10:
            WhichMove(2, 3, 0);
            break;
        case 11:
            WhichMove(2, 3, 3);
            break;
        default:
            break;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->x() > swidget->pos().x() && e->x() < swidget->pos().x() + swidget->width() && e->y() > 45 && e->y() < 45 + swidget->height()) {
        swidget->manager->getInitPos(e->x(),e->y());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (e->x() > swidget->pos().x() && e->x() < swidget->pos().x() + swidget->width() && e->y() > 45 && e->y() < 45 + swidget->height()) {
        if(e->buttons()&Qt::RightButton)
        {
            swidget->manager->executeRotateOperation(e->x(),e->y());
        }
        if(e->buttons()&Qt::LeftButton)
        {
            swidget->manager->executeTranslateOperation(e->x(),e->y());
        }
        swidget->updateGL();
        messageINstatusbar();
    }
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    if (e->x() > swidget->pos().x() && e->x() < swidget->pos().x() + swidget->width() && e->y() > 45 && e->y() < 45 + swidget->height()) {
        if(e->delta()>=0)
        {
            swidget->manager->executeScaleOperation(-0.1);
        }else
        {
            swidget->manager->executeScaleOperation(0.1);
        }
        swidget->updateGL();
        messageINstatusbar();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
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
        swidget->updateGL();
        break;
    case Qt::Key_Escape:
        close();
    }
}

void MainWindow::on_action_O_triggered()
{
    filename = QFileDialog::getOpenFileName(this, "Open An Object", QDir::currentPath(), "Object files(*.obj);;All files(*.*)");
    if (!filename.isNull()) { //用户选择了文件
        QFileInfo fileinfo = QFileInfo(filename);
        file_name = fileinfo.fileName();
        swidget->obj = new MYOBJECT(filename);
    }
    else { // 用户取消选择
    }
}

void MainWindow::on_action_S_triggered()
{
    FileName = QFileDialog::getSaveFileName(this, "Save An Object", QDir::currentPath(), "Object files(*.obj);;All files(*.*)");
    if (!FileName.isNull()){ //用户选择了文件
        QFileInfo fileinfo = QFileInfo(filename);
        File_Name = fileinfo.fileName();
        QFile f(FileName);
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream txtOutput(&f);
        for (int i = 0; i < swidget->obj->points.size(); i++) {
            MYPOINT p = swidget->obj->points[i];
            txtOutput << "v  " << p.px << " " << p.py << " " << p.pz << endl;
        }
        for (int i = 0; i < swidget->obj->faces.size(); i++) {
            MYFACE f = swidget->obj->faces[i];
            txtOutput << "f  " << f.pa + 1 << " " << f.pb + 1 << " " << f.pc + 1 << endl;
        }
        f.close();
    }
    else { // 用户取消选择
    }
}

int MainWindow::makeRandomNumber()
{
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    qsrand(time(NULL));
    return qrand() % 12;
}

void MainWindow::WhichMove(int pos, int m, int n)
{
    int random = makeRandomNumber();
    double Steps = 20, Step;
    if (random % 2 == 0) Step = 1;
    else Step = -1;
    for (int i = 0; i < Steps; i++) {
        switch (pos) {
        case 1:
            for (int i = 0; i < 4; i++) {
                swidget->obj->ffd->controlpoints[m][i][n].NowMove(Step);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                swidget->obj->ffd->controlpoints[m][n][i].NowMove(Step);
            }
            break;
        default: // is 0
            for (int i = 0; i < 4; i++) {
                swidget->obj->ffd->controlpoints[i][m][n].NowMove(Step);
            }
            break;
        }

        for (int i = 0; i < swidget->obj->points.size(); i++) {
            swidget->obj->points[i] = swidget->obj->ffd->calculateBezier(swidget->obj->normalizedpoints[i]);
        }
        swidget->updateGL();
    }
    for (int i = 0; i < Steps; i++) {
        switch (pos) {
        case 1:
            for (int i = 0; i < 4; i++) {
                swidget->obj->ffd->controlpoints[m][i][n].NowMove(-Step);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                swidget->obj->ffd->controlpoints[m][n][i].NowMove(-Step);
            }
            break;
        default: // is 0
            for (int i = 0; i < 4; i++) {
                swidget->obj->ffd->controlpoints[i][m][n].NowMove(-Step);
            }
            break;
        }

        for (int i = 0; i < swidget->obj->points.size(); i++) {
            swidget->obj->points[i] = swidget->obj->ffd->calculateBezier(swidget->obj->normalizedpoints[i]);
        }
        swidget->updateGL();
    }
}
