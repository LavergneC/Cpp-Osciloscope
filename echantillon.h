#ifndef ECHANTILLON_H
#define ECHANTILLON_H

#include <QList>
#include <iostream>
#include <sstream>
#include <QTextStream>
#include <stdlib.h>

class Echantillon
{
private:
    QList<double> valeurs;
public:
    Echantillon();
    int periode();
};

#endif // ECHANTILLON_H
