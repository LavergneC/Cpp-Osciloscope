#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    /*Création de deux grilles pour y ranger nos widgets*/
    maGrille  = new QGridLayout(this);
    QGridLayout* maGrille2 = new QGridLayout();
    QGridLayout* grilleBoutons = new QGridLayout();

    /*Canvas responsable de l'affichage*/
    myC = new MyCanvas(this);

    /*SerialCapture, responsable de la récupération des données*/
    myS = new SerialCapture();

    connect(myS,&SerialCapture::finTram,myC,&MyCanvas::updateCanvas);
    connect(myS,&SerialCapture::newValue,myC,&MyCanvas::newValue);

    /*Création des widgets*/
    QPushButton* boutonQ = new QPushButton(this);
    boutonQ->setText("Quitter");
    QPushButton* boutonR = new QPushButton(this);
    boutonR->setText("Reset");
    QPushButton* boutonC = new QPushButton(this);
    boutonC->setText("Couleur");
    QPushButton* boutonP = new QPushButton(this);
    boutonP->setText("Pause/Play");
    QPushButton* boutonT = new QPushButton(this);
    boutonT->setText("Trigger");

    zoomParam = new Param("Zoom",50,200,100,this);
    echelleXParam = new Param("EchelleX",50,200,100,this);
    echelleYParam = new Param("EchelleY",50,200,100,this);

    /* Notre ecran est dans la première case de la grille principale*/
    maGrille->addWidget(myC,0,0);

    /* On ajoute ensuit notre bouton et nos sliders dans la grille secondaire*/
    maGrille2->addWidget(echelleXParam,0,0);
    maGrille2->addWidget(echelleYParam,0,1);
    maGrille2->addWidget(zoomParam,1,0);

    /* On ajoute les boutons dans la grille des boutons */
    grilleBoutons->addWidget(boutonQ,2,1);
    grilleBoutons->addWidget(boutonC,0,0);
    grilleBoutons->addWidget(boutonR,0,1);
    grilleBoutons->addWidget(boutonP,1,0);
    grilleBoutons->addWidget(boutonT, 1, 1);

    /* On place la grille des bouton dans la grille des widgets */
    maGrille2->addLayout(grilleBoutons,1,1);

    /*On place la grille secondaire dans la grille principale, dans la deuxième case */
    maGrille->addLayout(maGrille2,1,0);

    connect(zoomParam, &Param::valeurChangee, myC, &MyCanvas::changerZoom);
    connect(echelleXParam, &Param::valeurChangee, myC, &MyCanvas::changerEchelleX);
    connect(echelleYParam, &Param::valeurChangee, myC, &MyCanvas::changerEchelleY);

    connect(boutonR, &QPushButton::clicked, zoomParam, &Param::reset);
    connect(boutonR, &QPushButton::clicked, echelleXParam, &Param::reset);
    connect(boutonR, &QPushButton::clicked, echelleYParam, &Param::reset);

    connect(boutonC, &QPushButton::clicked, myC, &MyCanvas::changerCouleur);
    connect(boutonQ, &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(boutonP, &QPushButton::clicked, myC, &MyCanvas::pausePlay);

    connect(boutonT, &QPushButton::clicked, myC, &MyCanvas::trigger);
}

MainWindow::~MainWindow()
{

}
