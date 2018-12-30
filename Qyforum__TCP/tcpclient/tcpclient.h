#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QtNetWork>
#include <QObject>
#include "user.h"
enum Symbol { LOGIN, LEVEL, POSTLIST, CHOOSEPOST };
class tcpclient: public QObject
{
    Q_OBJECT
private:
    QTcpSocket *tcpSocket;
    QString Qmessage;
    std::string message; //存放从服务器接收到的字符串
    quint16 blockSize; //存放文件的大小信息  可以不要
    std::string uid;
    std::string upw;
public slots:
    void login_2();
    void login_3(int ptype);

    void newConnect(std::string a, int b); //连接服务器
    void readMessage();  //接收数据
    void sendMessage();

    void state_initial();
    void state_login();
    void state_typechoose();
    void state_postview();
    void state_inpost();
signals:
    void goto_send();   //每次接受一次，才允许下一次发送
    void goto_login();
    void goto_level(int);
    void initial();
    void log_in();
    void Register();
    void postview();
    void typechoose();
    void inpost();
public:
    void start_send(Symbol s, std::string m = "");
    bool visitor;
    Userptr thisuser;
    tcpclient();
    std::string getmessage();
    void start_read();
};

#endif // TCPCLIENT_H


