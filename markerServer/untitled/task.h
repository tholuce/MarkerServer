#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QRunnable>

class Task : public QObject, public QRunnable
{
    Q_OBJECT
    QString request;
public:
     Task(QString request);
protected:
    void run();

signals:
    SendPictr(QString,QByteArray);
};

#endif // TASK_H
