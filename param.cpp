#include "param.h"

Param::Param(QString nom, int min, int max, int valInit, QWidget *parent) : QWidget (parent)
{
    valReset = valInit;
    box = new QHBoxLayout(this);
    this->setGeometry(0,0,300,50);
    this->setFixedHeight(45);

    label = new QLabel();
    label->setText(nom);

    box->addWidget(label);

    lcd = new QLCDNumber();
    lcd->display(valInit);
    lcd->move(130,0);
    box->addWidget(lcd);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(min,max);
    slider->setValue(valInit);
    slider->move(200,0);
    box->addWidget(slider);

    connect(slider,SIGNAL(valueChanged(int)),lcd,SLOT(display(int)));
    connect(slider,SIGNAL(valueChanged(int)),this, SIGNAL(valeurChangee(int)));
}

Param::~Param(){
    delete label;
    delete lcd;
    delete slider;
    delete box;
}

void Param::reset(){
    slider->setValue(valReset);
    lcd->display(valReset);
    emit valeurChangee(valReset);
}
