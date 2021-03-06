#include "mycanvas.h"
#include <QPainter>
#include "qnamespace.h"
#include <cmath>
#include <iostream>

MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent)
{
    setFixedSize(m_largeur, m_hauteur);
    QRect fondLabel;
    fondLabel.setCoords(0,0,30,10);
    fondLabel.setRect(0,0,30,10);
    labelRunPause = new QLabel(this);
    labelRunPause->setText("RUNNING");
    labelRunPause->setFrameRect(fondLabel);

    /* Les valeurs stockées à afficher */
    values = new QList<short>;

    /* Initialisation d'attributs qui pourront être changes par slot*/
    m_zoom = 100;
    m_echelleX = 100;
    m_echelleY = 100;
    couleur = Qt::black;
}
/*
 * Fonction pour adapter l'affichage et gestion des zoom
*/
QPointF MyCanvas::coo(double x, double y)
{
    return QPointF(x*(double)m_unite * (m_zoom/100) * (m_echelleX/100), y * (double)m_unite * (m_zoom/100) * (m_echelleY/100) * -1);
}

void MyCanvas::paintEvent(QPaintEvent *)
{
    // debugSetValue(); /*Debug ONLY*/

    QPainter maFeuille(this);

    maFeuille.save();

    maFeuille.translate(m_largeur/2,m_hauteur/2); // Permet de placer l'origine

    QPen myPen = *new QPen(Qt::blue,2*(m_zoom/100),Qt::SolidLine);
    //maFeuille.setPen(myPen); // utile ?

     /* Dessin des lignes verticales et des graduations verticales*/

    for(int x = -500; x < 501; x+=10){
        maFeuille.setPen(myPen);
        maFeuille.drawLine(coo(x,-500),coo(x,500));
        myPen = *new QPen(Qt::blue,2*(m_zoom/100),Qt::SolidLine);
        maFeuille.setPen(myPen);
        maFeuille.drawLine(coo(x,-2),coo(x,2));
    }

    /* Dessin des lignes horizontales et des graduations horizontales */
    for(int y = -500; y < 501; y+=10){
        myPen = *new QPen(Qt::gray,2*(m_zoom/100),Qt::SolidLine);
        maFeuille.setPen(myPen);
        maFeuille.drawLine(coo(-500,y),coo(500,y));
        myPen = *new QPen(Qt::blue,2*(m_zoom/100),Qt::SolidLine);
        maFeuille.setPen(myPen);
        maFeuille.drawLine(coo(-2,y),coo(2,y));
    }

    /* Dessin des axes */
    myPen = *new QPen(Qt::blue,2*(m_zoom/100),Qt::SolidLine);
    maFeuille.setPen(myPen);
    maFeuille.drawLine(coo(-500,0),coo(500,0));
    maFeuille.drawLine(coo(0,-500),coo(0,500));

    /* Dessin des valeurs stockées dans values */
    maFeuille.setPen(QPen(couleur,3*(m_zoom/100),Qt::SolidLine));
    for(double x = -500; x < 500 && values->size() == 1000; x++){
       maFeuille.drawPoint(coo(x,values->at(x+500)));
    }

    maFeuille.restore();

    updateCanvas();
}

/*
 * Fonciton pour changer l'attribut couleur de manière cyclique
 * a activer par un bouton
 */
void MyCanvas::changerCouleur()
{
    static Qt::GlobalColor tab[14] = {
              Qt::white, Qt::darkGray,Qt:: gray, Qt:: red,Qt:: green, Qt:: blue,
              Qt:: cyan,Qt:: yellow,Qt:: darkRed,Qt:: darkGreen,Qt:: darkBlue,Qt::  darkCyan,
              Qt:: darkMagenta,Qt:: darkYellow
            };

    static int indexCouleur = 0;
    couleur = tab[indexCouleur];
    indexCouleur = (indexCouleur + 1) % 15;

    update();
}

/*
 * SlotQ pour mettre la jour nos valeur pour l'affichage
 */
void MyCanvas::changerZoom(int z)
{
   // m_unite = (float)z * 0.05;
    m_zoom = z;
    update();
}

void MyCanvas::changerEchelleX(int ex){
    m_echelleX = ex;
    update();
}

void MyCanvas::changerEchelleY(int eY){
    m_echelleY = eY;
    update();
}

/*
 *  Slot pour ajouter une nouvelle valeur à notre liste de valeur
 */
void MyCanvas::newValue(short v){
    if(enPause)
        return;
    /* Variable de test conernant l'enregistrement des valeurs */
    static bool testTrigger = 0;

    v /=100; // remise à l'echelle, très moche
    static unsigned short index = 0;

    if(enTrigger && !testTrigger)
    {
        index=0;
        if ( ( v <= valueTrigger && v+30 >= valueTrigger) || (v >= valueTrigger && v-30 <= valueTrigger) )
            testTrigger=1;
    }

    /*
     * La taille de la liste vallue est limite à 1000 car le camvas fait 1000 pixels
     * Si la liste n'est pas pleine on ajoute une nouvelle valeur
     * Sinon on remplace une valeur
     */
    if (values->size()<1000){
        values->push_back(v);
        index = (index+1)%1000;
    }
    else{
        if(!enTrigger || (enTrigger && testTrigger) ){
            values->replace(index,v);
            index = (index+1)%1000;
        }
        if(index == 0)
            testTrigger=0;
    }
}

void MyCanvas::updateCanvas(){
    update();
}

void MyCanvas::debugSetValue(){
   /* for(int i = 0; i<250; i++)
        newValue(10*100);

    int c = -100;
    for (int i =0; i<500; i++){
        newValue(c*100);
        c++;

    }*/
    for(int i = -500; i<500; i++)
        newValue(abs(i)*100/2);

}
void MyCanvas::pausePlay(){
    enPause ^= 1;
}

void MyCanvas::trigger(){
    enTrigger ^= 1;
    valueTrigger = values->at(15);
    changerCouleur();
}
