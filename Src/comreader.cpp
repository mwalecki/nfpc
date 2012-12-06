#include "comreader.h"
#include "mainwindow.h"
#include <QtGui>
#include "nfv2.h"
#include <string>
#include "qextserialport/qextserialport.h"

extern NF_STRUCT_ComBuf     NFComBuf;
//extern Ui::MainWindow       *myui;

ComReader::ComReader(Ui::MainWindow *myui): ui(myui)
{
    commandCnt = 0;
}

void ComReader::run(){
    qDebug() << "Started ComReader thread " << thread()->currentThreadId();
    while(1){
       // qDebug() << "hello from ComReader thread " << thread()->currentThreadId();
        this->doStuff();
    }
}

void ComReader::doStuff(){
    static uint8_t commArr[16], commCnt, bytesReceived;

    if(this->rxCnt == 255)
        this->rxCnt = 0;

    if(port->read((char*)&(this->rxBuf[this->rxCnt]), 1) > 0){
    //    this->NFComBufMutex->lock();
        if((bytesReceived = NF_Interpreter(&NFComBuf, this->rxBuf, &(this->rxCnt), commArr, &commCnt)) > 0){
            ComReader::publishReadPreview(this->rxBuf, bytesReceived+1);
            ComReader::updateDisplayValues();
        }
    //    this->NFComBufMutex->unlock();
    }
//    if(ReadUart(&(this->rxBuf[this->rxCnt]), 1) > 0){
//    //    this->NFComBufMutex->lock();
//        if((bytesReceived = NF_Interpreter(&NFComBuf, this->rxBuf, &(this->rxCnt), commArr, &commCnt)) > 0){
//            ComReader::publishReadPreview(this->rxBuf, bytesReceived+1);
//            ComReader::updateDisplayValues();
//        }
//    //    this->NFComBufMutex->unlock();
//    }
    else {
        QThread::msleep(50);
    }
}

void ComReader::publishReadPreview(uint8_t *arr, uint8_t cnt){
    std::string sbuf;
    char stemp[4];

    for(int i=0; i<cnt; i++){
        sprintf(stemp, "%02X;", arr[i]);
        sbuf.append(stemp);
    }
    this->readPreview->setText(sbuf.c_str());
}

void ComReader::updateDisplayValues(){
    ComReader::dataReceived();
}
