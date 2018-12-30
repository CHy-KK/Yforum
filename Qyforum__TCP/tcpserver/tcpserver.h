#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QtNetWork>
#include <iostream>
#include <QObject>
#include <QString>
#include "data.h"
class TCP : public QObject
{
    Q_OBJECT
private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpServerConnection;
    QString Qmessage;
    std::string message;
    Userptr thisuser;
public slots:
    void sendMessage();
    void acceptConnection();
    void getdata();
    void start_read();
signals:
    void goto_read();   //  每次发送一次之后，才允许下一次读取
public:
    TCP();
    void start_send(string m);
    void setuser(Userptr tu);
};

#endif // TCPSERVER_H
