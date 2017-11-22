#include "controlwidget.h"
#include <QDebug>

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    for (int i = 0; i < 64; i++) {
        buttonClicked[i] = false;
        QString str = QString::number(i, 10);
        controlbutton[i] = new QPushButton(str, this);
        connect(controlbutton[i], &QPushButton::clicked, this, &ControlWidget::clickButton);
    }

    QHBoxLayout* layout0 = new QHBoxLayout;
        QVBoxLayout* layout1 = new QVBoxLayout;
            QHBoxLayout* layout1_1 = new QHBoxLayout;
            addButton(layout1_1, 0);
            QHBoxLayout* layout1_2 = new QHBoxLayout;
            addButton(layout1_2, 1);
            QHBoxLayout* layout1_3 = new QHBoxLayout;
            addButton(layout1_3, 2);
            QHBoxLayout* layout1_4 = new QHBoxLayout;
            addButton(layout1_4, 3);
        layout1->addLayout(layout1_1);
        layout1->addLayout(layout1_2);
        layout1->addLayout(layout1_3);
        layout1->addLayout(layout1_4);
    layout0->addLayout(layout1);
    layout0->addSpacing(10);
        QVBoxLayout* layout2 = new QVBoxLayout;
            QHBoxLayout* layout2_1 = new QHBoxLayout;
            addButton(layout2_1, 4);
            QHBoxLayout* layout2_2 = new QHBoxLayout;
            addButton(layout2_2, 5);
            QHBoxLayout* layout2_3 = new QHBoxLayout;
            addButton(layout2_3, 6);
            QHBoxLayout* layout2_4 = new QHBoxLayout;
            addButton(layout2_4, 7);
        layout2->addLayout(layout2_1);
        layout2->addLayout(layout2_2);
        layout2->addLayout(layout2_3);
        layout2->addLayout(layout2_4);
    layout0->addLayout(layout2);
    layout0->addSpacing(10);
        QVBoxLayout* layout3 = new QVBoxLayout;
            QHBoxLayout* layout3_1 = new QHBoxLayout;
            addButton(layout3_1, 8);
            QHBoxLayout* layout3_2 = new QHBoxLayout;
            addButton(layout3_2, 9);
            QHBoxLayout* layout3_3 = new QHBoxLayout;
            addButton(layout3_3, 10);
            QHBoxLayout* layout3_4 = new QHBoxLayout;
            addButton(layout3_4, 11);
        layout3->addLayout(layout3_1);
        layout3->addLayout(layout3_2);
        layout3->addLayout(layout3_3);
        layout3->addLayout(layout3_4);
    layout0->addLayout(layout3);
    layout0->addSpacing(10);
        QVBoxLayout* layout4 = new QVBoxLayout;
            QHBoxLayout* layout4_1 = new QHBoxLayout;
            addButton(layout4_1, 12);
            QHBoxLayout* layout4_2 = new QHBoxLayout;
            addButton(layout4_2, 13);
            QHBoxLayout* layout4_3 = new QHBoxLayout;
            addButton(layout4_3, 14);
            QHBoxLayout* layout4_4 = new QHBoxLayout;
            addButton(layout4_4, 15);
        layout4->addLayout(layout4_1);
        layout4->addLayout(layout4_2);
        layout4->addLayout(layout4_3);
        layout4->addLayout(layout4_4);
    layout0->addLayout(layout4);

    QHBoxLayout* layoutxyz = new QHBoxLayout;
        sliderx = new QSlider(this);
        sliderx->setObjectName("xSlider");
        sliderx->setRange(-10, 10);
        sliderx->setValue(0);
        sliderx->setOrientation(Qt::Horizontal);
        sliderx->setTickPosition(QSlider::TicksAbove);
        QLabel* labelx = new QLabel(this);
        labelx->setText("x");
        layoutxyz->addWidget(labelx);
        layoutxyz->addWidget(sliderx);
    layoutxyz->addSpacing(20);
        slidery = new QSlider(this);
        slidery->setObjectName("ySlider");
        slidery->setRange(-10, 10);
        slidery->setValue(0);
        slidery->setOrientation(Qt::Horizontal);
        slidery->setTickPosition(QSlider::TicksAbove);
        QLabel* labely = new QLabel(this);
        labely->setText("y");
        layoutxyz->addWidget(labely);
        layoutxyz->addWidget(slidery);
    layoutxyz->addSpacing(20);
        sliderz = new QSlider(this);
        sliderz->setObjectName("zSlider");
        sliderz->setRange(-10, 10);
        sliderz->setValue(0);
        sliderz->setOrientation(Qt::Horizontal);
        sliderz->setTickPosition(QSlider::TicksAbove);
        QLabel* labelz = new QLabel(this);
        labelz->setText("z");
        layoutxyz->addWidget(labelz);
        layoutxyz->addWidget(sliderz);

    QVBoxLayout* superlayout = new QVBoxLayout;
    superlayout->addLayout(layout0);
    superlayout->addSpacing(20);
    superlayout->addLayout(layoutxyz);
    setLayout(superlayout);
}

void ControlWidget::addButton(QHBoxLayout *l, int n)
{
    n *= 4;
    for (int i = 0; i < 4; i++) {
        l->addWidget(controlbutton[n + i]);
    }
}

void ControlWidget::clickButton()
{
    QPushButton* tmp = (QPushButton*)sender();
    int buttonNumber = tmp->text().toInt();
    buttonClicked[buttonNumber] = !buttonClicked[buttonNumber];
    if (buttonClicked[buttonNumber]) {
        controlbutton[buttonNumber]->setFlat(true);
    }
    else {
        controlbutton[buttonNumber]->setFlat(false);
    }
}
