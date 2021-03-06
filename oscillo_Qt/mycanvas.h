#ifndef MYCANVAS_H
#define MYCANVAS_H
#include <QWidget>
#include <QLabel>

class MyCanvas : public QWidget
{
    Q_OBJECT
public:
    MyCanvas(QWidget* parent);
    QPointF coo(double x, double y);

protected:
    void paintEvent(QPaintEvent *);

private :
    QLabel* labelRunPause;
    const static int m_largeur = 1000, m_hauteur = 600;
    float m_unite = 5;
    Qt::GlobalColor couleur;

    double m_zoom;
    double m_echelleX;
    double m_echelleY;

    bool enPause = 0;
    bool enTrigger = 0;

    short valueTrigger;

    QList<short>*values;

    void debugSetValue();

public slots:
    void changerCouleur();
    void changerZoom(int z);
    void changerEchelleX(int ex);
    void changerEchelleY(int ey);
    void pausePlay();

    void newValue(short v);
    void updateCanvas();

    void trigger();
};

#endif // MYCANVAS_H
