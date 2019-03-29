#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycanvas.h"
#include "serialcapture.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    /*Canvas responsable de l'affichage*/
    MyCanvas *myC = new MyCanvas(this);

    /*SerialCapture, responsable de la récupération des données*/
    SerialCapture * myS = new SerialCapture();

    connect(myS,&SerialCapture::finTram,myC,&MyCanvas::updateCanvas);
    connect(myS,&SerialCapture::newValue,myC,&MyCanvas::newValue);
}

MainWindow::~MainWindow()
{

}
