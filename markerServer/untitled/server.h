#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QTcpServer
{
public:
    Server(int port);

   protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
