#ifndef MYCANVAS_H
#define MYCANVAS_H
#include <QWidget>

class MyCanvas : public QWidget
{
    Q_OBJECT
public:
    MyCanvas(QWidget* parent);
    QPointF coo(double x, double y);

protected:
    void paintEvent(QPaintEvent *);

private :
    const static int m_largeur = 1000, m_hauteur = 600;
    float m_unite = 5;
    Qt::GlobalColor couleur;

    double m_zoom;

    QList<unsigned int>*values;

public slots:
    void changerCouleur();
    void changerZoom(int z);
    void newValue(short v);
    void updateCanvas();
};

#endif // MYCANVAS_H
