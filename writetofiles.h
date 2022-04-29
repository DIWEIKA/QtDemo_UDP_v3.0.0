#ifndef WRITETOFILES_H
#define WRITETOFILES_H

#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class DealMsg;
class  WriteToFiles;
class UDP_Recv;

class WriteToFiles : public QThread
{
public:
    WriteToFiles(UDP_Recv* udp_Recv);

    QTimer* udpTimer;
    UDP_Recv* udp_recv;
    bool isTimeUpdate;
    QDateTime dateTime; //��ǰϵͳʱ��
    string saveFolder;//�洢Ŀ¼���ļ��У�
    QString saveFilename1; //CH1�洢�ļ���
    QString saveFilename2;
    QString saveFilename3;
    QString saveFilename4;
    QString saveFilenameAll;
    QString file1;
    QString file2;
    QString file3;
    QString file4;
    QString fileAll;
    ofstream outfile1;//CH1
    ofstream outfile2;
    ofstream outfile3;
    ofstream outfile4;
    ofstream outfileAll;
    int PeakNum=31;
    shared_ptr<CirQueue<unsigned char>> CHdata;

protected:
    //QThread���麯��
    //�̴߳�����
    //����ֱ�ӵ��ã�ͨ��start()��ӵ���
    void run();

signals:

};

#endif // WRITETOFILES_H
