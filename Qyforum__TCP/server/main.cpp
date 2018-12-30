#include <QCoreApplication>
#include "tcpserver.h"
using namespace std;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TCP ex;
    ex.sendMessage();
    return a.exec();
}
