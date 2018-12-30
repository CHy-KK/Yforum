#include "data.h"
#include "tcpserver.h"
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
extern TCP ex;
Comment::Comment()
{
}
Comment::Comment(int no, string c, string id, int pid, int r)
{
    PID = pid;
    No = no;
    content = QString::fromStdString(c);
    reply = r;
    userid = QString::fromStdString(id);
    const time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A", localtime(&t));
    comtime = (string)tmp;
}
Comment::Comment(int no, string c, string id, int r, string time, int pid)
{
    PID = pid;
    No = no;
    content = QString::fromStdString(c);
    reply = r;
    userid = QString::fromStdString(id);
    comtime = time;
}

string Comment::getcontent() {
    return content.toStdString();
}

void Comment::dec()
{
    No--;
}

int Comment::getNo()
{
    return No;
}

int Comment::getreply()
{
    return reply;
}

int Comment::getpid()
{
    return PID;
}

string Comment::gettime()
{
    return comtime;
}

string Comment::getuserid()
{
    return userid.toStdString();
}

ostream &operator<<(ostream &out, Comment *thiscom)
{
    QSqlQuery Cquery("SELECT*from comment");
    Cquery.prepare("INSERT INTO comment(REPLY,NO,USERID,CONTENT,COMTIME,POSTID)"
                  "VALUES (:REPLY,:NO,:USERID,:CONTENT,:COMTIME,:POSTID)");
    Cquery.bindValue(":REPLY", thiscom->getreply());
    Cquery.bindValue(":NO", thiscom->getNo());
    Cquery.bindValue(":USERID", QString::fromStdString(thiscom->getuserid()));
    Cquery.bindValue(":CONTENT", QString::fromStdString(thiscom->getcontent()));
    Cquery.bindValue(":COMTIME", QString::fromStdString(thiscom->gettime()));
    Cquery.bindValue(":POSTID",thiscom->getpid());
    Cquery.exec();
    out<<"add successfully"<<endl;
    return out;
}

Comment::~Comment()
{
}

