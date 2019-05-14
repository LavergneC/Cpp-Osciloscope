#include "echantillon.h"

Echantillon::Echantillon()
{
    /* Lecture et enregristrement desm ots du fichier*/
    QFile file("/home/clement/Qt/12_oscilo/courbe.dat");

    if(!file.open(QIODevice::ReadOnly))
        std::cerr<<"Fichier non trouvé !"<<std::endl;
    QTextStream in(&file);
    while(!in.atEnd())
        valeurs.push_back(in.readLine().toDouble());
}

int Echantillon::periode()
{
    double d_max = -10000;
    for(int nbE = 0; nbE < valeurs.size(); nbE++){
        if (valeurs.at(nbE) > d_max)
            d_max = valeurs.at(nbE);
    }
    std::cout<<"maxD = "<<d_max<<std::endl;

    int i_max = (int)(d_max * 1000);
    std::cout<<"maxI = "<<i_max<<std::endl;

    int pos_fist_max = 0;
    for(int nbE = 0; nbE < valeurs.size(); nbE++){
        if ((int)(valeurs.at(nbE)*1000) == i_max){
            pos_fist_max = nbE;
            break;
        }
    }
    std::cout<<"pos_fist_max = "<<pos_fist_max<<std::endl;

    int pos_sec_max= pos_fist_max;
     for(int nbE2 = pos_fist_max+10; nbE2 < valeurs.size(); nbE2++){
        if((int)(valeurs.at(nbE2)*1000) == i_max){
            pos_sec_max = nbE2;
            break;
        }
    }
    if (pos_sec_max == pos_fist_max)
         return -1;

    std::cout<<"pos_sec_max = "<<pos_sec_max<<std::endl;
    std::cout<<"Preriode = "<<pos_sec_max - pos_fist_max<<std::endl;
    return pos_sec_max - pos_fist_max;
}
