#include "writetofiles.h"

WriteToFiles::WriteToFiles(UDP_Recv* udp_Recv)
{
    udp_recv = udp_Recv;

    CHdata = make_shared<CirQueue<unsigned char>>(udp_recv->LenoUDP);
}

void WriteToFiles::run()
{
    qDebug() << "TimeUpdate" << endl;

    //���µ�ǰʱ��
    dateTime = QDateTime::currentDateTime();

    saveFolder =  string("F:/Desktop/UDPConnect/data/");

    //    saveFilename1 = QString(saveFolder.c_str())+QString("/[CH1][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    //    saveFilename2 = QString(saveFolder.c_str())+QString("/[CH2][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    //    saveFilename3 = QString(saveFolder.c_str())+QString("/[CH3][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    //    saveFilename4 = QString(saveFolder.c_str())+QString("/[CH4][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilenameAll = QString(saveFolder.c_str())+QString("[All][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");


    //���ļ�
    //   outfile1.open(saveFilename1.toStdString().data(),ofstream::binary);
    //   outfile2.open(saveFilename2.toStdString().data(),ofstream::binary);
    //   outfile3.open(saveFilename3.toStdString().data(), ofstream::binary);
    //   outfile4.open(saveFilename4.toStdString().data(), ofstream::binary);
    outfileAll.open(saveFilenameAll.toStdString().data(), ofstream::binary);

    //���ļ�ʧ�����������
    //    if (!outfile1.is_open() || !outfile2.is_open() || !outfile3.is_open() || !outfile4.is_open()) return;
    if (!outfileAll.is_open()) return;

    unsigned int sizeoCHdata; //CHdata�ĳ���

    for(int i = 0; i< SaveNumber; i++){

//        if(!udp_recv->CHdataArray[i]->isEmpty()){

//            sizeoCHdata = udp_recv->CHdataArray[i]->size();

//            CHdata = udp_recv->CHdataArray[i];

//            for(unsigned int j=0; j<sizeoCHdata; ++j){
//                outfileAll.write((const char*)CHdata->begin(),sizeof(unsigned char));
//                CHdata->pop();
//            }
//         }
        if(udp_recv->CHdataArray[i]->isEmpty())
            continue;
        else
        {
            sizeoCHdata = udp_recv->CHdataArray[i]->size();

//            CHdata = udp_recv->CHdataArray[i];

            for(unsigned int j=0; j<sizeoCHdata; ++j){
                outfileAll.write((const char*)udp_recv->CHdataArray[i]->begin(),sizeof(unsigned char));
                udp_recv->CHdataArray[i]->pop();
            }

            udp_recv->CHdataArray[i]->clear();
        }
    }

    qDebug()<<"ofstream writing over ! "<<endl;


    //close stream
    //    outfile1.close();
    //    outfile2.close();
    //    outfile3.close();
    //    outfile4.close();

    outfileAll.close();

    qDebug()<< "WriteToFiles Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;
}

