#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QtNetWork>
#include <iostream>
#include <QObject>
#include <QString>

class TCP : public QObject
{
    Q_OBJECT
private:
    QTcpServer *tcpServer;
public slots:
    void sendMessage();

public:
    TCP();
};

#endif // TCPSERVER_H
