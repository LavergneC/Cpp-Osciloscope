#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "param.h"
#include "mycanvas.h"
#include "serialcapture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGridLayout* maGrille;
    MyCanvas *myC;
    SerialCapture * myS;

    Param* zoomParam;
    Param* echelleXParam;
    Param* echelleYParam;
    Param* triger;
};

#endif // MAINWINDOW_H
