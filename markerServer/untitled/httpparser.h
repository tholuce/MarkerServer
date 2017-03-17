#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <QString>
#include <map>
#include <QPair>
#include <QImage>
#include <QColor>
//ac5c6c6901622d63936ba04ed6aabdf30901fdea15fa1b0ff4d4d18d0cbbf174
using namespace std;

class HTTPParser
{

    QString request;
    QString method,path,version;
    map<QString,QString> *elseInfo;
    map<QString,QString> *pathReq;

public:
    HTTPParser(QString request);
    void parse();
    QString GetMethod();
    QString GetPath();
    QString GetVersion();
    QPair<QString, QByteArray> generateResponse();
    int code();
    QImage MakeGradient(QColor from, QColor to, QImage source, QColor change, QColor rangeColor);
    void NextColor(int *steps, QColor &curr);
    QImage MakeColor(QColor color, QImage source, QColor change, QColor rangeColor);
    void parsePathReq(QString path);
};

#endif // HTTPPARSER_H
