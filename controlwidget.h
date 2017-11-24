#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = nullptr);

    QPushButton* controlbutton[64];
    QPushButton* playButton;
    bool buttonClicked[64];
    void addButton(QHBoxLayout* l, int n);
    void clickButton();

    QSlider* sliderx;
    QSlider* slidery;
    QSlider* sliderz;

signals:

public slots:
};

#endif // CONTROLWIDGET_H
