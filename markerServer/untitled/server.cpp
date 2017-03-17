#include "server.h"
#include <client.h>
#include <iostream>
#include <QFile>


using namespace std;
QFile *file;


Server::Server(int port)
{
    file=new QFile("asd.txt");
    file->open(QIODevice::WriteOnly);
        if (this->listen(QHostAddress::Any,port))
        {
           cout<<"Start Server";
        }
        else
        {
            cout<<this->errorString().toStdString();
        }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    client *clientSocket=new client(0,socketDescriptor);
    file->write(clientSocket->socket->peerAddress().toString().toStdString().data());
    file->flush();
}

