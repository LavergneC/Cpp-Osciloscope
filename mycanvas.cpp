#include "mycanvas.h"
#include <QPainter>
#include "qnamespace.h"
#include <cmath>
#include <iostream>

MyCanvas::MyCanvas(QWidget *parent) : QWidget(parent)
{
    setFixedSize(m_largeur, m_hauteur); //marche po

    /* Les valeurs stockées à afficher */
    values = new QList<unsigned int>;

    /* Initialisation d'attributs qui pourront êtr changes par slot*/
    m_zoom = 100;
    couleur = Qt::black;
}
/*
 * Fonction pour adapter l'affichage et gestion du zoom
*/
QPointF MyCanvas::coo(double x, double y)
{
    return QPointF(x*(double)m_unite * (m_zoom/100), y*(double)m_unite * (m_zoom/100));
}

void MyCanvas::paintEvent(QPaintEvent *)
{
    QPainter maFeuille(this);

    maFeuille.save();

    maFeuille.translate(m_largeur/2,m_hauteur/2); // Permet de placer l'origine

    QPen myPen = *new QPen(Qt::blue,2*(m_zoom/100),Qt::SolidLine);
    maFeuille.setPen(myPen); // utile ?

     /* Dessin des lignes verticales et des graduations verticales*/
    for(int x = -500; x < 501; x+=10){
        myPen = *new QPen(Qt::gray,2*(m_zoom/100),Qt::SolidLine);
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
    maFeuille.setPen(QPen(couleur,2*(m_zoom/100),Qt::SolidLine));
    for(double x = -500; x < 500 && values->size() == 1000; x+=0.1){
       maFeuille.drawPoint(coo(x,values->at(x+500)));
    }

    maFeuille.restore();
}

/*
 * Fonciton pour changer l'attribut couleur de manière cyclique
 * a activer par un bouton
 */
void MyCanvas::changerCouleur()
{
    static Qt::GlobalColor tab[19] = {
              Qt::color0,Qt::color1,Qt::black,Qt::white, Qt::darkGray,Qt:: gray,Qt::lightGray,Qt:: red,Qt:: green, Qt:: blue,
              Qt:: cyan,Qt:: yellow,Qt:: darkRed,Qt:: darkGreen,Qt:: darkBlue,Qt::  darkCyan,
              Qt:: darkMagenta,Qt:: darkYellow,Qt::transparent
            };

    static int indexCouleur = 0;
    couleur = tab[indexCouleur];
    indexCouleur = (indexCouleur+1) %20;

    update();
}

/*
 * Slot pour mettre la jour la valeur du zoom
 */
void MyCanvas::changerZoom(int z)
{
   // m_unite = (float)z * 0.05;
    m_zoom = z;
    update();
}

/*
 *  Slot pour ajouter une nouvelle valeur à notre liste de valeur
 */
void MyCanvas::newValue(short v){
    v /=100; // remise à l'echelle, très moche
    static unsigned short index = 0;

    /* La taille de la liste vallue est limite à 1000 car le camvas fait 1000 pixels
     * Si la liste n'est pas plein on ajoute une nouvelle valeur
     * Sinon on remplace une valeur
     */
    if (values->size()<1000){
        values->push_back(v);
    }
    else
        values->replace(index,v);
    index = (index+1)%1000;
}
/*
 * Voilà voilà...
 */
void MyCanvas::updateCanvas(){
    update();
}
