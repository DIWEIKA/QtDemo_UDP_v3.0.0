#include "recvdata.h"

Recvdata::Recvdata(SOCKET socket, Ui::MainWindow *ui)
{
    Recvsocket = socket;

    UI = ui;

    //share memory to clientAddr
    ZeroMemory(&clientAddr, sizeof(clientAddr));

    //CHdata��ʼ�� ��
    CHdata=make_shared<CirQueue<float>>(LenoUDP);

    CHdata2 = make_shared<CirQueue<char>>(LenoUDP);
}

Recvdata::~Recvdata()
{

}

void Recvdata:: UDPRecieve()
{
       //RecvBuf << UDP
       readDatagram();

       if(hasRecv == SOCKET_ERROR)
       {
             qDebug()<<"Error receiving from client"<<WSAGetLastError()<< endl;
             return;
        }

       //Display message and client info
//       char clientIP[256];
//       ZeroMemory(clientIP,256);
//       inet_nt(AF_INET, &clientAddr.sin_addr, clientIP, 256); //clientIP << clientAddr.sin_addr

       qDebug()<<"Recv Message :"<<RecvBuf<< endl;

       //CHData << RecvBuf
       getDatafromBufToCHdata();
}

void Recvdata::readDatagram()
{
    //int LenoBuf
    LenoBuf = 8192;

    //share memory to RecvBuf
    ZeroMemory(RecvBuf,LenoBuf);

    int clientAddrLen = sizeof(clientAddr);

    //��ȡ�Է����͵����ݣ�������RecvBuf
    hasRecv = recvfrom(Recvsocket,RecvBuf,LenoBuf, 0, (SOCKADDR* )&clientAddr, &clientAddrLen);
}

void Recvdata:: changeFileNameOnce()
{
    //���µ�ǰʱ��
    dateTime = QDateTime::currentDateTime();

    saveFolder =  string("F:/Desktop/UDPConnect/data/");

    saveFilename1 = QString(saveFolder.c_str())+QString("/[CH1][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilename2 = QString(saveFolder.c_str())+QString("/[CH2][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilename3 = QString(saveFolder.c_str())+QString("/[CH3][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

}

void Recvdata::getDatafromBufToCHdata()
{

    for(int i=0; i<LenoBuf; i++)
     {
        char usCHDATA =RecvBuf[i];

        CHdata->push(float(usCHDATA));

        //����
        CHdata2->push(usCHDATA);
    }
}

void Recvdata:: WriteToFilesWith3Channels()
{
    //���ļ�
   outfile1.open(saveFilename1.toStdString().data(),ofstream::binary);
   outfile2.open(saveFilename2.toStdString().data(),ofstream::binary);
   outfile3.open(saveFilename3.toStdString().data(), ofstream::binary);

    //���ļ�ʧ�����������
    if (!outfile1.is_open() || !outfile2.is_open() || !outfile3.is_open()) return;

    //���Ⱥ�˳��CH1��CH2��CH3�����ݷֿ��洢
    for(unsigned int i=0; i<CHdata2->size()/3; ++i)
    {
        outfile1.write((const char*)CHdata2->begin(),sizeof (char));
        CHdata2->pop();
        outfile2.write((const char*)CHdata2->begin(),sizeof (char));
        CHdata2->pop();
        outfile3.write((const char*)CHdata2->begin(),sizeof (char));
        CHdata2->pop();
    }

    //clear CHdata
    CHdata2->clear();

    qDebug()<<"ofstream writing over ! "<<endl;

    qDebug()<<"CHdata have been cleared ! "<<endl;

}

void Recvdata::closeStream()
{
    //�ر������
    outfile1.close();
    outfile2.close();
    outfile3.close();
}

void Recvdata::CloseUDP()
{
         //close Recvsocket
        qDebug()<<"finished receiving, closing socket"<<endl;

        closesocket(Recvsocket);

        //Shutdown Winsock
        qDebug()<<"Exiting..."<<endl;

        WSACleanup();
}

