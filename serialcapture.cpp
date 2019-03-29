#include "serialcapture.h"

/*
 * Code copier-coller du cour du prof
 */
SerialCapture::SerialCapture()
{
    m_serial=new QSerialPort(this);
    m_serial->setPortName("/dev/ttyUSB0");
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if(!m_serial->open(QIODevice::ReadOnly)) {
        qDebug() <<QObject::tr("Je ne peux pas ouvrir le port série %1...").arg(m_serial->portName());
    }
    connect(m_serial,static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this,&SerialCapture::handleError);
    connect(m_serial,&QSerialPort::readyRead,this,&SerialCapture::readData);
}

/*
 * Code copier-coller du cour du prof
 */
void SerialCapture::handleError(QSerialPort::SerialPortError error)
{
    if(error==QSerialPort::ResourceError) {
        qDebug() <<QObject::tr("Erreur critique : %1").arg(m_serial->errorString());
    }
}

void SerialCapture::readData()
{
    QByteArray buf=m_serial->readAll();
    std::string buffS = buf.toStdString();

    // Découpage de la longue tram reçue à l'aide des \n
    QList<QByteArray> laListe = buf.split('\n');

    /* Suppression des données qui pourrait être troquées */
    laListe.pop_front();
    laListe.pop_back();

    /* Chaque valeur est émises par un signal */
    foreach (auto v, laListe) {
        std::cout<<"recu : "<<v.toStdString()<<std::endl;
        emit newValue(v.toShort());
    }
    emit finTram(); // Fin tram permet de mettre à jour de canvas une seul fois par lecture
}
