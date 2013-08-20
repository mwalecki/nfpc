#include "comsender.h"
#include "mainwindow.h"
#include <QtGui>
#include "nfv2.h"
#include <string>
#include "qextserialport/qextserialport.h"

extern NF_STRUCT_ComBuf     NFComBuf;
//extern Ui::MainWindow       *myui;

ComSender::ComSender(Ui::MainWindow *myui): ui(myui)
{
    commandCnt = 0;
}

void ComSender::run(){
    qDebug() << "Started ComSender thread " << thread()->currentThreadId();
    while(1){
    //    qDebug() << "hello from ComSender thread " << thread()->currentThreadId();
        this->doStuff();
        QThread::msleep(ui->sbPeriod->value());
    }
}

void ComSender::doStuff(){
//    this->NFComBufMutex->lock();
    ComSender::updateCommandArray();
    this->txCnt = NF_MakeCommandFrame(&NFComBuf, this->txBuf, this->commandArray, this->commandCnt, this->txAddr);
//    this->NFComBufMutex->unlock();
    ComSender::publishSendPreview(this->txBuf, this->txCnt);
    //WriteUart(this->txBuf, this->txCnt);
    port->write((const char*)this->txBuf, this->txCnt);
}

void ComSender::publishSendPreview(uint8_t *arr, uint8_t cnt){
    std::string sbuf;
    char stemp[4];

    for(int i=0; i<cnt; i++){
        sprintf(stemp, "%02X;", arr[i]);
        sbuf.append(stemp);
    }
    this->sendPreview->setText(sbuf.c_str());
}

void ComSender::updateCommandArray(){
    commandCnt = 0;
    if(ui->cbEnDrive->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesSpeed;
        if(ui->pbGoFwd->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[1] = ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbGoRev->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = - ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[1] = - ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbGoRight->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[1] = - ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbGoLeft->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = - ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[1] = ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbMotor0Up->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[1] = 0;
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbMotor0Dn->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = - ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[1] = 0;
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbMotor1Up->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = 0;
            NFComBuf.SetDrivesSpeed.data[1] = ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbMotor1Dn->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = 0;
            NFComBuf.SetDrivesSpeed.data[1] = - ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbMotor2Up->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = 0;
            NFComBuf.SetDrivesSpeed.data[1] = 0;
            NFComBuf.SetDrivesSpeed.data[2] = ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbMotor2Dn->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = 0;
            NFComBuf.SetDrivesSpeed.data[1] = 0;
            NFComBuf.SetDrivesSpeed.data[2] = - ui->setMaxSpeed->value();
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
        else if(ui->pbMotor3Up->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = 0;
            NFComBuf.SetDrivesSpeed.data[1] = 0;
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = ui->setMaxSpeed->value();
        }
        else if(ui->pbMotor3Dn->isDown()){
            NFComBuf.SetDrivesSpeed.data[0] = 0;
            NFComBuf.SetDrivesSpeed.data[1] = 0;
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = - ui->setMaxSpeed->value();
        }
        else{
            NFComBuf.SetDrivesSpeed.data[0] = 0;
            NFComBuf.SetDrivesSpeed.data[1] = 0;
            NFComBuf.SetDrivesSpeed.data[2] = 0;
            NFComBuf.SetDrivesSpeed.data[3] = 0;
        }
    }
    if(ui->cbEnDrivePWM->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesPWM;
        if(ui->pbMotor0PWMUp->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = ui->setMaxPWM->value();
            NFComBuf.SetDrivesPWM.data[1] = 0;
            NFComBuf.SetDrivesPWM.data[2] = 0;
            NFComBuf.SetDrivesPWM.data[3] = 0;
        }
        else if(ui->pbMotor0PWMDn->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = - ui->setMaxPWM->value();
            NFComBuf.SetDrivesPWM.data[1] = 0;
            NFComBuf.SetDrivesPWM.data[2] = 0;
            NFComBuf.SetDrivesPWM.data[3] = 0;
        }
        else if(ui->pbMotor1PWMUp->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = 0;
            NFComBuf.SetDrivesPWM.data[1] = ui->setMaxPWM->value();
            NFComBuf.SetDrivesPWM.data[2] = 0;
            NFComBuf.SetDrivesPWM.data[3] = 0;
        }
        else if(ui->pbMotor1PWMDn->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = 0;
            NFComBuf.SetDrivesPWM.data[1] = - ui->setMaxPWM->value();
            NFComBuf.SetDrivesPWM.data[2] = 0;
            NFComBuf.SetDrivesPWM.data[3] = 0;
        }
        else if(ui->pbMotor2PWMUp->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = 0;
            NFComBuf.SetDrivesPWM.data[1] = 0;
            NFComBuf.SetDrivesPWM.data[2] = ui->setMaxPWM->value();
            NFComBuf.SetDrivesPWM.data[3] = 0;
        }
        else if(ui->pbMotor2PWMDn->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = 0;
            NFComBuf.SetDrivesPWM.data[1] = 0;
            NFComBuf.SetDrivesPWM.data[2] = - ui->setMaxPWM->value();
            NFComBuf.SetDrivesPWM.data[3] = 0;
        }
        else if(ui->pbMotor3PWMUp->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = 0;
            NFComBuf.SetDrivesPWM.data[1] = 0;
            NFComBuf.SetDrivesPWM.data[2] = 0;
            NFComBuf.SetDrivesPWM.data[3] = ui->setMaxPWM->value();
        }
        else if(ui->pbMotor3PWMDn->isDown()){
            NFComBuf.SetDrivesPWM.data[0] = 0;
            NFComBuf.SetDrivesPWM.data[1] = 0;
            NFComBuf.SetDrivesPWM.data[2] = 0;
            NFComBuf.SetDrivesPWM.data[3] = - ui->setMaxPWM->value();
        }
        else{
            NFComBuf.SetDrivesPWM.data[0] = 0;
            NFComBuf.SetDrivesPWM.data[1] = 0;
            NFComBuf.SetDrivesPWM.data[2] = 0;
            NFComBuf.SetDrivesPWM.data[3] = 0;
        }
    }
    if(ui->cbEnDriveCurrent->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesCurrent;
        if(ui->pbMotor0CurrentUp->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = ui->setMaxCurrent->value();
            NFComBuf.SetDrivesCurrent.data[1] = 0;
            NFComBuf.SetDrivesCurrent.data[2] = 0;
            NFComBuf.SetDrivesCurrent.data[3] = 0;
        }
        else if(ui->pbMotor0CurrentDn->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = - ui->setMaxCurrent->value();
            NFComBuf.SetDrivesCurrent.data[1] = 0;
            NFComBuf.SetDrivesCurrent.data[2] = 0;
            NFComBuf.SetDrivesCurrent.data[3] = 0;
        }
        else if(ui->pbMotor1CurrentUp->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = 0;
            NFComBuf.SetDrivesCurrent.data[1] = ui->setMaxCurrent->value();
            NFComBuf.SetDrivesCurrent.data[2] = 0;
            NFComBuf.SetDrivesCurrent.data[3] = 0;
        }
        else if(ui->pbMotor1CurrentDn->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = 0;
            NFComBuf.SetDrivesCurrent.data[1] = - ui->setMaxCurrent->value();
            NFComBuf.SetDrivesCurrent.data[2] = 0;
            NFComBuf.SetDrivesCurrent.data[3] = 0;
        }
        else if(ui->pbMotor2CurrentUp->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = 0;
            NFComBuf.SetDrivesCurrent.data[1] = 0;
            NFComBuf.SetDrivesCurrent.data[2] = ui->setMaxCurrent->value();
            NFComBuf.SetDrivesCurrent.data[3] = 0;
        }
        else if(ui->pbMotor2CurrentDn->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = 0;
            NFComBuf.SetDrivesCurrent.data[1] = 0;
            NFComBuf.SetDrivesCurrent.data[2] = - ui->setMaxCurrent->value();
            NFComBuf.SetDrivesCurrent.data[3] = 0;
        }
        else if(ui->pbMotor3CurrentUp->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = 0;
            NFComBuf.SetDrivesCurrent.data[1] = 0;
            NFComBuf.SetDrivesCurrent.data[2] = 0;
            NFComBuf.SetDrivesCurrent.data[3] = ui->setMaxCurrent->value();
        }
        else if(ui->pbMotor3CurrentDn->isDown()){
            NFComBuf.SetDrivesCurrent.data[0] = 0;
            NFComBuf.SetDrivesCurrent.data[1] = 0;
            NFComBuf.SetDrivesCurrent.data[2] = 0;
            NFComBuf.SetDrivesCurrent.data[3] = - ui->setMaxCurrent->value();
        }
        else{
            NFComBuf.SetDrivesCurrent.data[0] = 0;
            NFComBuf.SetDrivesCurrent.data[1] = 0;
            NFComBuf.SetDrivesCurrent.data[2] = 0;
            NFComBuf.SetDrivesCurrent.data[3] = 0;
        }
    }
    if(ui->cbEnDrivesPosition->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesPosition;
        NFComBuf.SetDrivesPosition.data[0] = ui->setDrivesPosition0->value();
        NFComBuf.SetDrivesPosition.data[1] = ui->setDrivesPosition1->value();
        NFComBuf.SetDrivesPosition.data[2] = ui->setDrivesPosition2->value();
        NFComBuf.SetDrivesPosition.data[3] = ui->setDrivesPosition3 ->value();
    }
    if(ui->cbEnServos->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_SetServosPosition;
        NFComBuf.SetServosPosition.data[0] = (ui->cbZeroSrv0->isChecked()? 0 : ui->setSrv0->value());
        NFComBuf.SetServosPosition.data[1] = (ui->cbZeroSrv1->isChecked()? 0 : ui->setSrv1->value());
        NFComBuf.SetServosPosition.data[2] = (ui->cbZeroSrv2->isChecked()? 0 : ui->setSrv2->value());
        NFComBuf.SetServosPosition.data[3] = (ui->cbZeroSrv3->isChecked()? 0 : ui->setSrv3->value());
        NFComBuf.SetServosPosition.data[4] = (ui->cbZeroSrv4->isChecked()? 0 : ui->setSrv4->value());
        NFComBuf.SetServosPosition.data[5] = (ui->cbZeroSrv5->isChecked()? 0 : ui->setSrv5->value());
        NFComBuf.SetServosPosition.data[6] = (ui->cbZeroSrv6->isChecked()? 0 : ui->setSrv6->value());
        NFComBuf.SetServosPosition.data[7] = (ui->cbZeroSrv7->isChecked()? 0 : ui->setSrv7->value());
    }
    if(ui->cbEnDigitalOut->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_SetDigitalOutputs;
        NFComBuf.SetDigitalOutputs.data[0] =
                ((ui->cbDOut1_0->isChecked() ? 1 : 0) << 0) |
                ((ui->cbDOut1_1->isChecked() ? 1 : 0) << 1) |
                ((ui->cbDOut1_2->isChecked() ? 1 : 0) << 2) |
                ((ui->cbDOut1_3->isChecked() ? 1 : 0) << 3) |
                ((ui->cbDOut1_4->isChecked() ? 1 : 0) << 4) |
                ((ui->cbDOut1_5->isChecked() ? 1 : 0) << 5) |
                ((ui->cbDOut1_6->isChecked() ? 1 : 0) << 6) |
                ((ui->cbDOut1_7->isChecked() ? 1 : 0) << 7);
        NFComBuf.SetDigitalOutputs.data[1] =
                ((ui->cbDOut2_0->isChecked() ? 1 : 0) << 0) |
                ((ui->cbDOut2_1->isChecked() ? 1 : 0) << 1) |
                ((ui->cbDOut2_2->isChecked() ? 1 : 0) << 2) |
                ((ui->cbDOut2_3->isChecked() ? 1 : 0) << 3) |
                ((ui->cbDOut2_4->isChecked() ? 1 : 0) << 4) |
                ((ui->cbDOut2_5->isChecked() ? 1 : 0) << 5) |
                ((ui->cbDOut2_6->isChecked() ? 1 : 0) << 6) |
                ((ui->cbDOut2_7->isChecked() ? 1 : 0) << 7);
        NFComBuf.SetDigitalOutputs.data[2] =
                ((ui->cbDOut3_0->isChecked() ? 1 : 0) << 0) |
                ((ui->cbDOut3_1->isChecked() ? 1 : 0) << 1) |
                ((ui->cbDOut3_2->isChecked() ? 1 : 0) << 2) |
                ((ui->cbDOut3_3->isChecked() ? 1 : 0) << 3) |
                ((ui->cbDOut3_4->isChecked() ? 1 : 0) << 4) |
                ((ui->cbDOut3_5->isChecked() ? 1 : 0) << 5) |
                ((ui->cbDOut3_6->isChecked() ? 1 : 0) << 6) |
                ((ui->cbDOut3_7->isChecked() ? 1 : 0) << 7);

        NFComBuf.SetDigitalOutputs.data[3] = NFComBuf.SetDigitalOutputs.data[0];
        NFComBuf.SetDigitalOutputs.data[4] = NFComBuf.SetDigitalOutputs.data[1];
        NFComBuf.SetDigitalOutputs.data[5] = NFComBuf.SetDigitalOutputs.data[2];
    }
    if(ui->cbEnAnalogIn->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_ReadAnalogInputs;
    }
    if(ui->cbEnReadDrivesPosition->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_ReadDrivesPosition;
    }
    if(ui->cbEnReadDrivesStatus->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_ReadDrivesStatus;
    }
    if(ui->cbEnDigitalIn->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_ReadDigitalInputs;
    }
    if(ui->cbEnVitals->isChecked()){
        commandArray[commandCnt++] = NF_COMMAND_ReadDeviceVitals;
    }
    if(ui->pbModeERStop->isDown()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesMode;
        NFComBuf.SetDrivesMode.data[0] = NF_DrivesMode_ERROR;
        NFComBuf.SetDrivesMode.data[1] = NF_DrivesMode_ERROR;
        NFComBuf.SetDrivesMode.data[2] = NF_DrivesMode_ERROR;
        NFComBuf.SetDrivesMode.data[3] = NF_DrivesMode_ERROR;
    }
    if(ui->pbModePWM->isDown()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesMode;
        NFComBuf.SetDrivesMode.data[0] = NF_DrivesMode_PWM;
        NFComBuf.SetDrivesMode.data[1] = NF_DrivesMode_PWM;
        NFComBuf.SetDrivesMode.data[2] = NF_DrivesMode_PWM;
        NFComBuf.SetDrivesMode.data[3] = NF_DrivesMode_PWM;
    }
    if(ui->pbModeCurrent->isDown()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesMode;
        NFComBuf.SetDrivesMode.data[0] = NF_DrivesMode_CURRENT;
        NFComBuf.SetDrivesMode.data[1] = NF_DrivesMode_CURRENT;
        NFComBuf.SetDrivesMode.data[2] = NF_DrivesMode_CURRENT;
        NFComBuf.SetDrivesMode.data[3] = NF_DrivesMode_CURRENT;
    }
    if(ui->pbModeSpeed->isDown()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesMode;
        NFComBuf.SetDrivesMode.data[0] = NF_DrivesMode_SPEED;
        NFComBuf.SetDrivesMode.data[1] = NF_DrivesMode_SPEED;
        NFComBuf.SetDrivesMode.data[2] = NF_DrivesMode_SPEED;
        NFComBuf.SetDrivesMode.data[3] = NF_DrivesMode_SPEED;
    }
    if(ui->pbModePosition->isDown()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesMode;
        NFComBuf.SetDrivesMode.data[0] = NF_DrivesMode_POSITION;
        NFComBuf.SetDrivesMode.data[1] = NF_DrivesMode_POSITION;
        NFComBuf.SetDrivesMode.data[2] = NF_DrivesMode_POSITION;
        NFComBuf.SetDrivesMode.data[3] = NF_DrivesMode_POSITION;
    }
    if(ui->pbModeSynchro->isDown()){
        commandArray[commandCnt++] = NF_COMMAND_SetDrivesMode;
        NFComBuf.SetDrivesMode.data[0] = NF_DrivesMode_SYNC_POS0;
        NFComBuf.SetDrivesMode.data[1] = NF_DrivesMode_SYNC_POS0;
        NFComBuf.SetDrivesMode.data[2] = NF_DrivesMode_SYNC_POS0;
        NFComBuf.SetDrivesMode.data[3] = NF_DrivesMode_SYNC_POS0;
    }
}
