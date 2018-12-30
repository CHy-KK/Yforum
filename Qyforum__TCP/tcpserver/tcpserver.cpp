#include "tcpserver.h"
#include "data.h"
extern vector<Userptr>Userlist;	//用户列表
extern map<PostType, vector<Postptr> >TotalPostList;    //映射类型总帖子列表，key为板块，value为板块下帖子列表
extern vector<Postptr>S_PostList;  //运动板块帖子列表,类型为vector<Postptr>
extern vector<Postptr>A_PostList;  //动漫版块
extern vector<Postptr>Mu_PostList; //音乐版块
extern vector<Postptr>Mv_PostList; //电影板块
extern vector<Postptr>G_PostList;  //游戏板块
extern long PostID;         //帖子id
extern int S_num;
extern int A_num;
extern int Mu_num;
extern int Mv_num;
extern int G_num;

PostType str_to_e(string s)
{
    if(s == "sport")
        return Sport;
    else if(s == "anime")
        return Anime;
    else if(s == "music")
        return Music;
    else if(s == "movie")
        return Movie;
    else if(s == "game")
        return Game;
}

TCP::TCP() : QObject(nullptr)
{

}

void TCP::setuser(Userptr tu)
{
    thisuser = new normalUser;
    thisuser = tu;
}

void TCP::sendMessage()
{
    const char*mess = message.c_str();
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out<<QObject::tr(mess);
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    QObject::connect(clientConnection,SIGNAL(disconnected()),clientConnection,
           SLOT(deleteLater()));

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
    tcpServer->close();
    //发送数据成功后，显示提示
    std::cout<<"send message successful!!!"<<std::endl;
    emit goto_read();
}

void TCP::start_send(string m)
{
    message = m;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
     //连接信号和相应槽函数
    if(!tcpServer->listen(QHostAddress::LocalHost,6666))
        return;
}

/*
 *
 *
 * 接受部分
 *
 *
 */
void TCP::start_read()
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    if(!tcpServer->listen(QHostAddress::LocalHost,6666))
         return;
}

void TCP::acceptConnection()
{
    tcpServerConnection = tcpServer->nextPendingConnection();
    connect(tcpServerConnection,SIGNAL(readyRead()),this,
        SLOT(getdata()));
}

void TCP::getdata()
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_4_6);
    in >> Qmessage;
    std::cout <<   Qmessage.toStdString()<<std::endl;
    message = Qmessage.toStdString();
    tcpServer->close();
    string choose = message.substr(0,message.find_first_of(';'));
    std::cout<<"choose is : "<<choose<<std::endl;
    string tempm;
    if(choose == "login"){
        string id = message.substr(message.find_first_of(';')+1);
        std::cout<<"id is : "<<id<<std::endl;
        Userptr thisuser;
        tempm = thisuser->log_in(id);
        if(tempm != "login;unsuccessful")   //客户端先获取第一个分号前的字符串，判断种类，然后看后面是否是unsuccessful
            tempm = "login;;" + tempm;
    }
    else if(choose == "level") {
        tempm = "level;";
        if(thisuser->getlevel()){
            switch(thisuser->getmtype()){
            case Sport:
                tempm += "0";
                break;
            case Anime:
                tempm += "1";
                break;
            case Music:
                tempm += "2";
                break;
            case Movie:
                tempm += "3";
                break;
            case Game:
                tempm += "4";
                break;
            }
        } else {
            tempm += "-1";
        }
    }
    else if (choose == "postlist") {
        tempm = "postlist;";
        thisuser->curtype = str_to_e(message.substr(message.find_last_of(';') + 1));
        iteratorpp it_pp = TotalPostList.find(thisuser->curtype);
        if(it_pp->second.begin() == it_pp->second.end())
            tempm += "nopost";
        for (iteratorp it_p = it_pp->second.begin(); it_p != it_pp->second.end(); it_p++) {
            tempm += "--------------------------------------\n";
            tempm += "post ID: " + to_string((*it_p)->getPid()) + '\n';
            tempm += "Title: " + (*it_p)->gettitle() + '\n';
            tempm += "Content: " + (*it_p)->getcontent() + '\n';
            tempm += "user: " + (*it_p)->getuserid() + '\n';
            tempm += "time: " + (*it_p)->gettime() + '\n';
            tempm += "this post has " + to_string((*it_p)->getNcm()) + " comments now" + '\n';
        }
    }
    else if (choose == "choosepost") {
        tempm = "choosepost;";
        string post_choose = message.substr(message.find_first_of(';') + 1);
        bool iffind = false;
        iteratorpp it_pp = TotalPostList.find(thisuser->curtype);
        for (iteratorp it_p = it_pp->second.begin(); it_p != it_pp->second.end(); it_p++) {
            if (to_string((*it_p)->getPid()) == post_choose) {
                tempm += "----------------------------------------\nTitle: " + (*it_p)->gettitle() + '\n';
                tempm += "Content: " + (*it_p)->getcontent() + '\n';
                Postptr thispost = *it_p;
                for (iteratorc it_c = thispost->getcomment()->begin(); it_c != thispost->getcomment()->end(); it_c++) {
                    tempm += "......................\n";
                    tempm += (*it_c)->gettime() + ':' + to_string((*it_c)->getNo()) + " floor, username: " + (*it_c)->getuserid() + '\n';
                    if ((*it_c)->getreply() > 0) {
                        tempm += "reply to " + to_string((*it_c)->getreply()) + " floor: ";
                    }
                    tempm += (*it_c)->getcontent() + '\n';
                }
                iffind = true;
                break;
            }
        }
        if (!iffind)
            tempm += "nopost";
    }
    std::cout<<"ready to send: "<<tempm<<std::endl;
    std::cout<<tempm<<endl;
    start_send(tempm);
}
