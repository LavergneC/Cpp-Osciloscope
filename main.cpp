#include "mainwindow.h"
#include <QApplication>
#include "echantillon.h"
#include <iostream>
#include "serialcapture.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
/*
    Echantillon *e = new Echantillon();
    int c = e->periode();
*/
    //SerialCapture* sc = new SerialCapture();

    return a.exec();
}
