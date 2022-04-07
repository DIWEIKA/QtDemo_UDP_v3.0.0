#ifndef SENDDATA_H
#define SENDDATA_H

#include <fstream>
#include <sstream>
#include <QMainWindow>
#include <memory>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <winsock2.h>

class Senddata  : public QObject
{
public:
    Senddata(SOCKET socket, Ui::MainWindow *ui);
    ~Senddata();
    void ReadFromFiles(); //ifStream >> sendData
    void getConfig();  //sendData>>msgbuf
    void writeDatagram(); //msgbuf>>UDP
    void  closeUDP();

    Ui::MainWindow *UI;
    SOCKET Sendsocket;
    ifstream infile; //���ش���������
    QString file; //�����ļ�Ŀ¼
    QString saveFolder;
    string sendData; //����һ��UDP���ݣ�����8192Byte�ᶪ��������65535Byte���޷�����
    QByteArray msgbuf;
    QString DestIP;
    qint16 DestPort;
    sockaddr_in RecvAddr;//��������ַ
    quint16 RecvPort;//�������˿ں�
    int Lenobuf; //length of msgbuf
};

#endif // SENDDATA_H
