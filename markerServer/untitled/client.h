#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class client : public QObject
{
    Q_OBJECT
public:

    QTcpSocket *socket;
    explicit client(QObject *parent = 0,qintptr sockDesc=0);


public slots:
    void ReadAll();
    void SendResponce(QString responce, QByteArray addBody);

};

#endif // CLIENT_H
