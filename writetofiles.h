#ifndef WRITETOFILES_H
#define WRITETOFILES_H

#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include"dealmsg.h"

class DealMsg;
class  WriteToFiles;

class WriteToFiles : public QThread
{
public:
    WriteToFiles(DealMsg* dealmsg);

    QTimer* udpTimer;
    DealMsg* dealMsg;
    bool isTimeUpdate;
    QDateTime dateTime; //��ǰϵͳʱ��
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
    int PeakNum=31;

protected:
        //QThread���麯��
        //�̴߳�����
        //����ֱ�ӵ��ã�ͨ��start()��ӵ���
    void run();

signals:

};

#endif // WRITETOFILES_H
