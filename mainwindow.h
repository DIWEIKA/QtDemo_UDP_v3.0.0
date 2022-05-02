#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <winsock2.h>
#include <QQueue>
#include "CirQueue.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QtNetwork>
#include <recvdata.h>
#include <QtDebug>
#include <vector>
#include <windows.h>
#include <writetofiles.h>
#include <udp_recv.h>


typedef unsigned char BYTE;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Recvdata; //ʹ��ǰ������
class Senddata;
class DealMsg;
class WriteToFiles;
class UDP_Recv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

    QTimer* udpTimer;
    UDP_Recv* udp_recv;
    WriteToFiles* writeToFiles;
    bool isSave;
    bool isStart;
    bool isASCII;
    bool isHEX;

    void setLocalMsg();
    void OpenWriteToFilesThread();
    void stopThread();


private slots:

    void FinishUDP_RecvThread();
    void FinishWriteToFilesThread();
    void on_pushButton_Start_clicked();
    void on_pushButton_Stop_clicked();

    void on_pushButton_Clear_clicked();

    void on_checkBox_Save_clicked();

    void on_checkBox_ASCII_clicked();

    void on_checkBox_Hex_clicked();

private:
    bool isTimeUpdate;
};
#endif // MAINWINDOW_H
