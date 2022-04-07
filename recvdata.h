#ifndef RECVDATA_H
#define RECVDATA_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QQueue>
#include "CirQueue.h"
#include <memory>
#include <fstream>
#include <QtNetwork>
#include <sstream>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <winsock2.h>
#include <ws2tcpip.h>


 typedef unsigned char BYTE;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow;

class Recvdata : public QObject
{
public:
    Recvdata(SOCKET socket, Ui::MainWindow *ui);
    ~Recvdata();
    void readDatagram();//��ȡudp��Ϣ
    void getDatafromBufToCHdata();
    void changeFileNameOnce();//�������ɴ洢�ļ���
    void WriteToFilesWith3Channels();
    void closeStream();
    void UDPRecieve();
    void CloseUDP();

    Ui::MainWindow *UI;
    SOCKET Recvsocket;

    qint64 LenoUDP = 1366*60000;  //CHdata�ĳ��� ���Ϊ9223372036854775807
    string saveFolder;//�洢Ŀ¼���ļ��У�
    QString saveFilename1; //CH1�洢�ļ���
    QString saveFilename2;
    QString saveFilename3;
    QString file1;
    QString file2;
    QString file3;
    ofstream outfile1;//CH1
    ofstream outfile2;
    ofstream outfile3;
    QDateTime dateTime; //��ǰϵͳʱ��
    sockaddr_in clientAddr; //�ͻ��˵�ַ
    quint16 clientPort; //�ͻ��˶˿ں�
    QTimer* udpTimer; //��ʱ�� ������ʱ1����
    shared_ptr<CirQueue<float>> CHdata; //���Channel���ݵ�����
    shared_ptr<CirQueue<char>> CHdata2; //����
    char usCHDATA;
    qint64 LenoBuf;
    char RecvBuf[];
    int hasRecv;
    int PeakNum = 31;//��ֵ��

public slots:


private slots:


private:


};

#endif // RECVDATA_H
