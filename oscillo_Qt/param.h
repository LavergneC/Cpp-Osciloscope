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
    int valReset;

public:
    Param(QString nom, int min, int max, int valInit, QWidget *parent=nullptr);
    ~Param();

signals:
    void valeurChangee(int);
public slots:
    void reset();
};

#endif // PARAM_H
