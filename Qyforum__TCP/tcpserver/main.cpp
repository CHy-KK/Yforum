#include <QCoreApplication>
#include "tcpserver.h"
#include <iostream>
#include <QDebug>
#include "data.h"
using namespace std;
vector<Userptr>Userlist;	//用户列表
map<PostType, vector<Postptr> >TotalPostList;    //映射类型总帖子列表，key为板块，value为板块下帖子列表
vector<Postptr>S_PostList;  //运动板块帖子列表,类型为vector<Postptr>
vector<Postptr>A_PostList;  //动漫版块
vector<Postptr>Mu_PostList; //音乐版块
vector<Postptr>Mv_PostList; //电影板块
vector<Postptr>G_PostList;  //游戏板块
long PostID = 10001;
int S_num;
int A_num;
int Mu_num;
int Mv_num;
int G_num;

TCP ex;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TotalPostList.insert(pair<PostType, vector<Postptr> >(Sport, S_PostList));
    TotalPostList.insert(pair<PostType, vector<Postptr> >(Anime, A_PostList));
    TotalPostList.insert(pair<PostType, vector<Postptr> >(Music, Mu_PostList));
    TotalPostList.insert(pair<PostType, vector<Postptr> >(Movie, Mv_PostList));
    TotalPostList.insert(pair<PostType, vector<Postptr> >(Game, G_PostList));
    Administrator administrator1("YCH1", "imadministrator1");
    Administrator administrator2("YCH2", "imadministrator2");

    //链接数据库
    qDebug()<<QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setDatabaseName("Yforum1");
    db.setUserName("root");
    db.setPassword("123456");
    if (!db.open()) {
       cout << "error";
    }
    //QSqlQuery Uquery("SELECT*from user");

    //Moderator* dbmoderator;

    //从数据库导入用户信息
    db>>Userlist;
    //从数据库导入帖子
    db>>TotalPostList;
    ex.start_read();

    ex.connect(&ex,SIGNAL(goto_read()),&ex,SLOT(start_read()));

    return a.exec();
}
