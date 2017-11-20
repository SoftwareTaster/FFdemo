#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    layout->setStretchFactor(swidget, 5);
    layout->setStretchFactor(cwidget, 1);
    widget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
