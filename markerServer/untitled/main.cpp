#include <QCoreApplication>
#include <QTcpServer>
#include <server.h>
#include <iostream>
//ac5c6c6901622d63936ba04ed6aabdf30901fdea15fa1b0ff4d4d18d0cbbf174
using namespace std;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int port=25606;
        cout<<"Enter Port:"<<endl;
        //cin>>port;
        Server server(port);



    return a.exec();
}

