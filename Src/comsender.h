#ifndef COMSENDER_H
#define COMSENDER_H

#include <QThread>
#include <QMutex>
#include <qapplication.h>
#include <QLineEdit>
#include <inttypes.h>
#include "ui_mainwindow.h"

class QextSerialPort;

class ComSender : public QThread
{
    Q_OBJECT
public:
    ComSender(Ui::MainWindow *myui);
    void run();
    void doStuff();
    QLineEdit *sendPreview;
    QMutex *NFComBufMutex;
    QextSerialPort *port;
    uint8_t txAddr;

private:
    Ui::MainWindow *ui;
    uint8_t txBuf[256];
    uint8_t txCnt;
    uint8_t commandArray[16];
    uint8_t commandCnt;
    void publishSendPreview(uint8_t *arr, uint8_t cnt);
    void updateCommandArray();
};

#endif // COMSENDER_H
