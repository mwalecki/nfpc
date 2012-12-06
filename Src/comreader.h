#ifndef COMREADER_H
#define COMREADER_H

#include <QThread>
#include <QMutex>
#include <qapplication.h>
#include <QLineEdit>
#include <inttypes.h>
#include "ui_mainwindow.h"

class QextSerialPort;

class ComReader : public QThread
{
    Q_OBJECT
public:
    ComReader(Ui::MainWindow *myui);
    void run();
    void doStuff();
    QLineEdit *readPreview;
    QMutex *NFComBufMutex;
    QextSerialPort *port;

private:
    Ui::MainWindow *ui;
    uint8_t rxBuf[256];
    uint8_t rxCnt;
    uint8_t commandArray[16];
    uint8_t commandCnt;
    uint8_t txAddr;
    void publishReadPreview(uint8_t *arr, uint8_t cnt);
    void updateDisplayValues();
signals:
    void dataReceived();
};

#endif // COMREADER_H
