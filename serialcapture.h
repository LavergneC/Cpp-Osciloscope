#ifndef SERIALCAPTURE_H
#define SERIALCAPTURE_H

#include <QWidget>
#include <QtSerialPort/qserialport.h>
#include <QList>
#include <qwidget.h>
#include <qdebug.h>
#include <iostream>

class SerialCapture : public QWidget
{
    Q_OBJECT
private:
    QList<unsigned short> m_data; // utile ???
    QSerialPort *m_serial;

public:
    SerialCapture();

public slots:
    void handleError(QSerialPort::SerialPortError error);
    void readData();
signals :
    void finTram();
    void newValue(short v);
};

#endif // SERIALCAPTURE_H
