#include "httpparser.h"
#include <QStringList>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QDate>
#include <QBuffer>
//ac5c6c6901622d63936ba04ed6aabdf30901fdea15fa1b0ff4d4d18d0cbbf174
using namespace std;


static QString pathyk="C:\\Users\\Vasyl\\Desktop\\marker server\\build-untitled-Desktop_Qt_5_7_1_MinGW_32bit-Debug\\debug\\";


HTTPParser::HTTPParser(QString request):request(request){}

void HTTPParser::parse()
{
    QStringList list=request.split("\r\n");
    QStringList list1=list[0].split(" ",QString::SkipEmptyParts);
    method=list1[0];
    path=list1[1].remove(0,1);
    version=list1[2];
    elseInfo=new map<QString,QString>();

    for (int i=1;i<list.length();i++)
    {
        QStringList l=list[i].split(": ");
       if (l.length()>1)
        elseInfo->insert(std::pair<QString,QString>(l[0],l[1]));
    }
    parsePathReq(path);
}

void HTTPParser::parsePathReq(QString path)
{
    pathReq=new map<QString,QString>();

    QStringList p=path.split("?");
    if(p.length()>1)
    {
        this->path=p[0];
        QString req=p[1];
        p=req.split("&");
        if(p.length()>0)
        {
            for (int i=0;i<p.length();i++)
            {
                QStringList s=p.at(i).split("=");
                pathReq->insert(std::pair<QString,QString>(s[0],s[1]));

            }
        }
    }



}


QString HTTPParser::GetMethod(){return method;}

QString HTTPParser::GetPath(){return path;}

QString HTTPParser::GetVersion(){return version;}


int HTTPParser::code()
{
    int code=200;
    if (GetVersion().isEmpty()) return code;
    FILE *file=fopen(QString(pathyk+GetPath()+".png").toLatin1().data(),"r+");
    if (file==NULL) code=404;
    fclose(file);
    return code;
}




QPair<QString,QByteArray> HTTPParser::generateResponse()
{
    QPair<QString,QByteArray>response("",QByteArray());


        switch(code())
        {
        case 200:{

 QByteArray body;
 int size;

if (pathReq->find("type")!=pathReq->end())
{
    if(pathReq->at("type")=="gradient"&&pathReq->find("from")!=pathReq->end()&&pathReq->find("to")!=pathReq->end())
    {
        QImage img(pathyk+GetPath()+".png");
       QImage newImg=MakeGradient(QColor("#"+pathReq->at("from")),QColor("#"+pathReq->at("to")),img,QColor(255,255,255),QColor(0,0,0));
        QBuffer buff(&body);
        buff.open(QIODevice::WriteOnly);
        newImg.save(&buff,"PNG");

    }
    else if(pathReq->at("type")=="color"&&pathReq->find("color")!=pathReq->end())
    {
        QImage img(pathyk+GetPath()+".png");
        QImage newImg=MakeColor(QColor("#"+pathReq->at("color")),img,QColor(255,255,255),QColor(0,0,0));
        QBuffer buff(&body);
        buff.open(QIODevice::WriteOnly);
        newImg.save(&buff,"PNG");



    }
    else
    {
        QFile *file=new QFile(pathyk+GetPath()+".png");
        file->open(QIODevice::ReadOnly);
         body=file->readAll();
    }

}
else
{
    QFile *file=new QFile(pathyk+GetPath()+".png");
    file->open(QIODevice::ReadOnly);
     body=file->readAll();

}
size=body.length();

             response.first=GetVersion()+" 200 OK\r\n";
            if (GetVersion().indexOf("1.0")>=0)
            {
                   response.first+="Content-type: image/png; charset=utf-8\r\n";
                   response.first+="Content-Length: "+QString::number(size)+"\r\n\r\n";
                   response.second=body;

            }
            else if (GetVersion().indexOf("1.1")>=0)
            {
               response.first+="Content-type: image/png; charset=utf-8\r\n";
               response.first+="Content-Length: "+QString::number(size)+"\r\n\r\n";
               response.second=body;

            }

        };break;
        case 400:
        {};break;
        case 404:
        {
            QString body="\r\n<html><body>404 Not Found</body></html>";
            response.first=GetVersion()+" 404 Not Found\r\n";
           if (GetVersion().indexOf("1.0")>=0)
           {
                   response.first+="Connection: close\r\n";
                   response.first+="Content-Type: text/html; charset=utf8\r\n";
                   response.first+="Content-Length: "+QString::number(body.length())+"\r\n\r\n";
                   response.first+=body;

           }
           else if (GetVersion().indexOf("1.1")>=0)
           {

               response.first+="Connection: close\r\n";
               response.first+="Content-Type: text/html; charset=utf8\r\n";
               response.first+="Content-Length: "+QString::number(body.length())+"\r\n\r\n";
               response.first+=body;

           }

        };break;
        }
return response;

}


QImage HTTPParser::MakeColor(QColor color, QImage source, QColor change, QColor rangeColor)
{
QImage img(QSize(source.width(),source.height()),QImage::Format_ARGB32);
for (int i=0;i<img.height();i++)
    for (int j=0;j<img.width();j++)
    {
       if(QColor(source.pixel(j,i))==rangeColor) img.setPixel(j,i,source.pixel(j,i));
       else if(QColor(source.pixel(j,i))==change) img.setPixel(j,i,color.rgba());
        else
       {int black=QColor(source.pixel(j,i)).black();
           img.setPixel(j,i,QColor(color.red()==0||color.red()<black?0:color.red()-black,color.green()==0||color.green()<black?0:color.green()-black,color.blue()==0||color.blue()<black?0:color.blue()-black).rgba());
       }
    }

return img;
}

void HTTPParser::NextColor(int *steps,QColor &curr)
{
        int red=curr.red()+steps[0],
            green=curr.green()+steps[1],
            blue=curr.blue()+steps[2];
       curr=QColor(red,green,blue);
}

QImage HTTPParser::MakeGradient(QColor from,QColor to,QImage source,QColor change,QColor rangeColor)
{
QImage img(QSize(source.width(),source.height()),QImage::Format_ARGB32);

int *steps=new int[3]{(to.red()-from.red())/img.height(),(to.green()-from.green())/img.height(),(to.blue()-from.blue())/img.height()};
 QColor curr=from;
for (int i=0;i<img.height();i++)
{
        NextColor(steps,curr);
    for (int j=0;j<img.width();j++)
    {
       if(QColor(source.pixel(j,i))==rangeColor) img.setPixel(j,i,source.pixel(j,i));
       else if(QColor(source.pixel(j,i))==change) img.setPixel(j,i,curr.rgba());
        else
       {int black=QColor(source.pixel(j,i)).black();
           img.setPixel(j,i,QColor(curr.red()==0||curr.red()<black?0:curr.red()-black,curr.green()==0||curr.green()<black?0:curr.green()-black,curr.blue()==0||curr.blue()<black?0:curr.blue()-black).rgba());
       }
    }
}

return img;
}


































