#include "client.h"
#include <task.h>
#include <QThreadPool>
#include <iostream>
#include <QFile>
#include <iostream>
#include <fstream>
#include <ios>
#include <QFile>

using namespace std;

client::client(QObject *parent,qintptr sockDesc) : QObject(parent)
{
 this->socket=new QTcpSocket();
 this->socket->setSocketDescriptor(sockDesc);
    connect(socket,SIGNAL(readyRead()),SLOT(ReadAll()));

}

void client::ReadAll()
{
    qDebug()<<"Ready to Read...";

Task *task=new Task(socket->readAll());

connect(task,SIGNAL(SendPictr(QString,QByteArray)),SLOT(SendResponce(QString,QByteArray)));
connect(socket,SIGNAL(disconnected()),task,SLOT(deleteLater()));
QThreadPool::globalInstance()->start(task);


}

void client::SendResponce(QString response,QByteArray addBody)
{
   std::cout<<"sended";
 socket->write(response.toStdString().data()+addBody);
}

