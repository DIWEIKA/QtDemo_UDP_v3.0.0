#ifndef DEALMSG_H
#define DEALMSG_H

#include <QThread>
#include <QtNetwork>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class DealMsg;
class  WriteToFiles;

/*QThread DealMsg used for dealing UDP response*/

class DealMsg : public QThread
{
public:
    DealMsg(SOCKET socket);

    void setFlag();
    void resetFlag();

    SOCKET Recvsocket;
    char RecvBuf[];
    int hasRecv;
    QHostAddress clientAddr; //�ͻ���IP
    quint16 clientPort; //�ͻ���port
    shared_ptr<CirQueue<unsigned char>> CHdata2; //����
    qint64 LenoUDP = 65535*60*10;  //CHdata�ĳ��� ���Ϊ9223372036854775807
    qint64 LenoBuf = 65535;
     bool isDone;  //�ж��߳��Ƿ����

protected:

         void run();

signals:

};

#endif // DEALMSG_H
