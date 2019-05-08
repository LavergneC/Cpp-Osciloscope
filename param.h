#ifndef PARAM_H
#define PARAM_H

#include <QWidget>
#include <QLCDNumber>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

class Param : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout* box;
    QLabel* label;
    QLCDNumber* lcd;
    QSlider* slider;

public:
    Param(QString nom, int min, int max, int valInit, QWidget *parent=nullptr);
    ~Param();

signals:
    void valeurChangee(int);
};

#endif // PARAM_H
