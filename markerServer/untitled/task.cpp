#include "task.h"
#include <httpparser.h>

Task::Task(QString request):request(request)
{

}

void Task::run()
{
HTTPParser *parser =new HTTPParser(request);
parser->parse();
QPair<QString,QByteArray> resp=parser->generateResponse();
emit SendPictr(resp.first,resp.second);
}

