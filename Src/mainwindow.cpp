#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nfv2.h"
#include "nfv2_config.h"
#include "comsender.h"
#include "comreader.h"
#include "qextserialport/qextserialport.h"
#include "qextserialport/qextserialenumerator.h"

#include <QMessageBox>

extern NF_STRUCT_ComBuf	NFComBuf;
extern ComSender        *senderThread;
extern ComReader        *readerThread;
extern QMutex           *comBufMutex;
//extern Ui::MainWindow   *myui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    myui = ui;
    deviceConnected = false;
    commRunning = false;
    ui->setupUi(this);
    comBufMutex = new QMutex();

    senderThread = new ComSender(ui);
    senderThread->sendPreview = ui->leTransmit;
    senderThread->NFComBufMutex = comBufMutex;

    readerThread = new ComReader(ui);
    readerThread->readPreview = ui->leReceive;
    readerThread->NFComBufMutex = comBufMutex;

    NFv2_Config2(&NFComBuf, NF_TerminalAddress, ui->sbAddress->value());
    senderThread->txAddr = ui->sbAddress->value();
    on_pbRescan_clicked();

    QObject::connect(readerThread, SIGNAL(dataReceived(void)), this, SLOT(slot_dataReceived(void)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbConnect_clicked()
{
    if(deviceConnected)
    {
        if(commRunning){
            ui->pbConnect->setChecked(true);
            QMessageBox::information(NULL, "", "First stop communication");
        }
        else{
            readerThread->terminate();
            port->close();

            deviceConnected=false;
            ui->pbConnect->setText("Connect");
            ui->pbConnect->setChecked(false);
            ui->pbRescan->setDisabled(false);
        }
    }
    else
    {
        // #### QextSerialPort ####
        PortSettings settings = {BAUD57600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
        port = new QextSerialPort(ui->boxPortName->currentText(), settings, QextSerialPort::Polling);

        if(port->open(QIODevice::ReadWrite) == false)
        {
            ui->pbConnect->setChecked(false);
            QMessageBox::critical(NULL, "Connection error", "Unable to open port");
        }
        else
        {
            deviceConnected=true;
            ui->pbConnect->setText("Connected");
            ui->pbConnect->setChecked(true);
            ui->pbRescan->setDisabled(true);
            senderThread->port = port;
            readerThread->port = port;
            readerThread->start();
        }
    }
}

void MainWindow::on_pbRun_clicked()
{
    if(commRunning){
        senderThread->terminate();
        senderThread->wait();

        commRunning=false;
        ui->pbRun->setText("Run");
        ui->pbRun->setChecked(false);
        ui->pbStep->setDisabled(false);
    }
    else{
        if(deviceConnected){
            senderThread->start();

            commRunning=true;
            ui->pbRun->setText("Running");
            ui->pbRun->setChecked(true);
            ui->pbStep->setDisabled(true);
        }
        else{
            ui->pbRun->setChecked(false);
            QMessageBox::information(NULL, "", "First open COM port");
        }
    }
}

void MainWindow::on_pbStep_clicked()
{
    senderThread->doStuff();
}

void MainWindow::slot_dataReceived(){
    static int flipflop;

    flipflop = (flipflop ? 0 : 1);
    if(flipflop)
        ui->leReceive->setDisabled(true);
    else
        ui->leReceive->setDisabled(false);
    ui->pbarAnalogIn0->setValue(NFComBuf.ReadAnalogInputs.data[0]);
    ui->pbarAnalogIn1->setValue(NFComBuf.ReadAnalogInputs.data[1]);
    ui->pbarAnalogIn2->setValue(NFComBuf.ReadAnalogInputs.data[2]);
    ui->pbarAnalogIn3->setValue(NFComBuf.ReadAnalogInputs.data[3]);
    ui->pbarAnalogIn4->setValue(NFComBuf.ReadAnalogInputs.data[4]);
    ui->pbarAnalogIn5->setValue(NFComBuf.ReadAnalogInputs.data[5]);
    ui->pbarAnalogIn6->setValue(NFComBuf.ReadAnalogInputs.data[6]);
    ui->pbarAnalogIn7->setValue(NFComBuf.ReadAnalogInputs.data[7]);

    ui->pbarVitals0->setValue(NFComBuf.ReadDeviceVitals.data[0]);
    ui->pbarVitals1->setValue(NFComBuf.ReadDeviceVitals.data[1]);
    ui->pbarVitals2->setValue(NFComBuf.ReadDeviceVitals.data[2]);
    ui->pbarVitals3->setValue(NFComBuf.ReadDeviceVitals.data[3]);
    ui->pbarVitals4->setValue(NFComBuf.ReadDeviceVitals.data[4]);
    ui->pbarVitals5->setValue(NFComBuf.ReadDeviceVitals.data[5]);
    ui->pbarVitals6->setValue(NFComBuf.ReadDeviceVitals.data[6]);
    ui->pbarVitals7->setValue(NFComBuf.ReadDeviceVitals.data[7]);

    ui->dispReadDrivesPosition0->setValue(NFComBuf.ReadDrivesPosition.data[0]);
    ui->dispReadDrivesPosition1->setValue(NFComBuf.ReadDrivesPosition.data[1]);

    ui->cbDrivesStatusPosLimit0->setChecked((NFComBuf.ReadDrivesStatus.data[0] & NF_DrivesStatus_PositionLimit) ? true : false);
    ui->cbDrivesStatusSynchronized0->setChecked((NFComBuf.ReadDrivesStatus.data[0] & NF_DrivesStatus_Synchronized) ? true : false);
    ui->cbDrivesStatusOvercurrent0->setChecked((NFComBuf.ReadDrivesStatus.data[0] & NF_DrivesStatus_Overcurrent) ? true : false);
    ui->cbDrivesStatusError0->setChecked((NFComBuf.ReadDrivesStatus.data[0] & NF_DrivesStatus_Error) ? true : false);

    ui->cbDrivesStatusPosLimit1->setChecked((NFComBuf.ReadDrivesStatus.data[1] & NF_DrivesStatus_PositionLimit) ? true : false);
    ui->cbDrivesStatusSynchronized1->setChecked((NFComBuf.ReadDrivesStatus.data[1] & NF_DrivesStatus_Synchronized) ? true : false);
    ui->cbDrivesStatusOvercurrent1->setChecked((NFComBuf.ReadDrivesStatus.data[1] & NF_DrivesStatus_Overcurrent) ? true : false);
    ui->cbDrivesStatusError1->setChecked((NFComBuf.ReadDrivesStatus.data[1] & NF_DrivesStatus_Error) ? true : false);

    ui->cbDIn1_0->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<0)) ? true : false);
    ui->cbDIn1_1->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<1)) ? true : false);
    ui->cbDIn1_2->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<2)) ? true : false);
    ui->cbDIn1_3->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<3)) ? true : false);
    ui->cbDIn1_4->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<4)) ? true : false);
    ui->cbDIn1_5->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<5)) ? true : false);
    ui->cbDIn1_6->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<6)) ? true : false);
    ui->cbDIn1_7->setChecked((NFComBuf.ReadDigitalInputs.data[0] & (1<<7)) ? true : false);

    ui->cbDIn2_0->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<0)) ? true : false);
    ui->cbDIn2_1->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<1)) ? true : false);
    ui->cbDIn2_2->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<2)) ? true : false);
    ui->cbDIn2_3->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<3)) ? true : false);
    ui->cbDIn2_4->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<4)) ? true : false);
    ui->cbDIn2_5->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<5)) ? true : false);
    ui->cbDIn2_6->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<6)) ? true : false);
    ui->cbDIn2_7->setChecked((NFComBuf.ReadDigitalInputs.data[1] & (1<<7)) ? true : false);

    ui->cbDIn3_0->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<0)) ? true : false);
    ui->cbDIn3_1->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<1)) ? true : false);
    ui->cbDIn3_2->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<2)) ? true : false);
    ui->cbDIn3_3->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<3)) ? true : false);
    ui->cbDIn3_4->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<4)) ? true : false);
    ui->cbDIn3_5->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<5)) ? true : false);
    ui->cbDIn3_6->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<6)) ? true : false);
    ui->cbDIn3_7->setChecked((NFComBuf.ReadDigitalInputs.data[2] & (1<<7)) ? true : false);
}

void MainWindow::on_pbRescan_clicked()
{
    ui->boxPortName->clear();
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    foreach( QextPortInfo portinfo, ports ) {
        if(portinfo.vendorID
                || portinfo.portName == "/dev/ttyS0"
                || portinfo.portName == "/dev/ttyS1"
                || portinfo.portName == "/dev/ttyS2"
                || portinfo.portName == "/dev/ttyS3"
                || portinfo.portName == "/dev/ttyS3"
                || portinfo.portName == "COM1"
                || portinfo.portName == "COM2"
                || portinfo.portName == "COM3"
                || portinfo.portName == "COM4"){
            ui->boxPortName->addItem(portinfo.portName);
        }
    }
}

void MainWindow::on_sbAddress_valueChanged(int newAddress)
{
    NFv2_Config2(&NFComBuf, NF_TerminalAddress, newAddress);
    senderThread->txAddr = newAddress;
}
