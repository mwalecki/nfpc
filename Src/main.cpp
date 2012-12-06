#include <QtGui/QApplication>
#include "mainwindow.h"
#include "nfv2.h"

NF_STRUCT_ComBuf	NFComBuf;
uint8_t             crcTable[256];
ComSender           *senderThread;
ComReader           *readerThread;
QMutex              *comBufMutex;
//Ui::MainWindow      *myui;

int main(int argc, char *argv[])
{
    NFv2_CrcInit();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
