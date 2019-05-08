#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycanvas.h"
#include "serialcapture.h"
#include "param.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    /*Création de deux grilles pour y ranger nos widgets*/
    maGrille  = new QGridLayout(this);
    QGridLayout* maGrille2 = new QGridLayout();

    /*Canvas responsable de l'affichage*/
    MyCanvas *myC = new MyCanvas(this);

    /*SerialCapture, responsable de la récupération des données*/
    SerialCapture * myS = new SerialCapture();

    connect(myS,&SerialCapture::finTram,myC,&MyCanvas::updateCanvas);
    connect(myS,&SerialCapture::newValue,myC,&MyCanvas::newValue);

    /*Création des widgets*/
    QPushButton* boutonQ = new QPushButton(this);
    boutonQ->setText("Quitter");
    Param* zoomParam = new Param("Zoom",50,200,100,this);
    Param* echelleXParam = new Param("EchelleX",50,200,100,this);
    Param* echelleYParam = new Param("EchelleY",50,200,100,this);

    /* Notre ecran est dans la première case de la grille principale*/
    maGrille->addWidget(myC,0,0);

    /* On ajoute ensuit notre bouton et nos sliders dans la grille secondaire*/
    maGrille2->addWidget(echelleXParam,0,0);
    maGrille2->addWidget(echelleYParam,0,1);
    maGrille2->addWidget(zoomParam,1,0);
    maGrille2->addWidget(boutonQ,1,1);

    /*On place la grille segondaire dans la grille principale, dans le deuxième case */
    maGrille->addLayout(maGrille2,1,0);

    connect(boutonQ,&QPushButton::clicked,qApp, &QCoreApplication::quit);
    connect(zoomParam,&Param::valeurChangee,myC,&MyCanvas::changerZoom);
}

MainWindow::~MainWindow()
{

}
