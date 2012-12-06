#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comsender.h"
#include "comreader.h"
#include <QMutex>

namespace Ui {
class MainWindow;
}

class QextSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pbConnect_clicked();
    void on_pbRun_clicked();
    void on_pbStep_clicked();

    void on_pbRescan_clicked();

    void on_sbAddress_valueChanged(int arg1);

public slots:
    void slot_dataReceived();

private:
    Ui::MainWindow *ui;

    bool commRunning;
    bool deviceConnected;

    QextSerialPort *port;
};

#endif // MAINWINDOW_H
