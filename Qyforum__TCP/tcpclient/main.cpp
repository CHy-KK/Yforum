#include <QCoreApplication>
#include "tcpclient.h"
tcpclient ex;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    ex.connect(&ex,SIGNAL(initial()),&ex,SLOT(state_initial()));
    ex.connect(&ex,SIGNAL(log_in()),&ex,SLOT(state_login()));
    emit ex.initial();
    ex.connect(&ex,SIGNAL(typechoose()),&ex,SLOT(state_typechoose()));
    ex.connect(&ex,SIGNAL(postview()),&ex,SLOT(state_postview()));
    ex.connect(&ex,SIGNAL(inpost()),&ex,SLOT(state_inpost()));
    return a.exec();
}
