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

Post::Post()
{

}

Post::Post(string t, string c, PostType tp, string uid, int n) {
    PID = PostID;
    PostID++;
    title = QString::fromStdString(t);
    content = QString::fromStdString(c);
    Ncm = n;

    const time_t nowtime = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A", localtime(&nowtime));
    ptime = (string)tmp;

    type = tp;
    userid = QString::fromStdString(uid);
    thiscomment = new Commentlist;
    int ntp;
    switch (type)
    {
    case Sport:
        number = ++S_num;
        ntp = 0;
        break;
    case Anime:
        number = ++A_num;
        ntp = 1;
        break;
    case Music:
        number = ++Mu_num;
        ntp = 2;
        break;
    case Movie:
        number = ++Mv_num;
        ntp = 3;
        break;
    case Game:
        number = ++G_num;
        ntp = 4;
        break;
    default:
        break;
    }

    //将帖子添加到数据库

}

ostream &operator<<(ostream &out, Post *thispost)
{
    QSqlQuery Pquery("SELECT*from post");
    Pquery.prepare("INSERT INTO post(PID,NUMBER,TYPE,USERID,TITLE,CONTENT,PTIME,NCM)"
                  "VALUES (:PID,:NUMBER,:TYPE,:USERID,:TITLE,:CONTENT,:PTIME,:NCM)");
    Pquery.bindValue(":PID", thispost->getPid());
    Pquery.bindValue(":NUMBER", thispost->getnumber());
    Pquery.bindValue(":TYPE", thispost->gettype());
    Pquery.bindValue(":USERID", QString::fromStdString(thispost->getuserid()));
    Pquery.bindValue(":TITLE", QString::fromStdString(thispost->gettitle()));
    Pquery.bindValue(":CONTENT", QString::fromStdString(thispost->getcontent()));
    Pquery.bindValue(":PTIME", QString::fromStdString(thispost->gettime()));
    Pquery.bindValue(":NCM", thispost->getNcm());
    Pquery.exec();
    out<<"add successfully"<<endl;
    return out;
}

Post::Post(string t, string c, PostType tp, string uid, int n, string dbtime, int pid) {
    PID = pid;
    if(PostID <= pid)
        PostID++;
    title = QString::fromStdString(t);
    content = QString::fromStdString(c);
    Ncm = n;
    ptime = dbtime;

    type = tp;
    userid = QString::fromStdString(uid);
    thiscomment = new Commentlist;
    switch (type)
    {
    case Sport:
        number = ++S_num;
        break;
    case Anime:
        number = ++A_num;
        break;
    case Music:
        number = ++Mu_num;
        break;
    case Movie:
        number = ++Mv_num;
        break;
    case Game:
        number = ++G_num;
        break;
    default:
        break;
    }
}

int Post::getPid() {
    return PID;
}

int Post::getnumber() {
    return number;
}

int Post::getNcm()
{
    return Ncm;
}

int Post::gettype()
{
    switch (type) {
    case Sport:
        return 0;
        break;
    case Anime:
        return 1;
        break;
    case Music:
        return 2;
        break;
    case Movie:
        return 3;
        break;
    case Game:
        return 4;
        break;
    default:
        break;
    }
}

string Post::getuserid()
{
    return userid.toStdString();
}

string Post::gettitle() {
    return title.toStdString();
}

string Post::getcontent() {
    return content.toStdString();
}

string Post::gettime() {
    return ptime;
}

void Post::setNcm()
{
    Ncm++;
}

vector<Commentptr>* Post::getcomment() {
    return thiscomment;
}

void Post::addcommet(string c, string id, int reply, string time, int pid)
{
    Commentptr newcom = new Comment(++Ncm, c, id, reply, time, pid);
    thiscomment->push_back(newcom);
}

void Post::addcommet(string c, string id, int reply, int PID)
{
    Ncm++;
    Commentptr newcom = new Comment(Ncm, c, id, PID, reply);
    thiscomment->push_back(newcom);
    QSqlQuery Pqeury;
    Pqeury.prepare("update post set NCM = :NCM where PID = :PID");
    Pqeury.bindValue(":NCM",Ncm);
    cout<<Ncm<<endl;
    cout<<PID<<endl;
    Pqeury.bindValue(":PID",PID);
    Pqeury.exec();

    cout<<newcom;
}

int Post::deletecomment(int num, string id, int pid)
{
    int result = 0;
    for (iteratorc it_c = thiscomment->begin(); it_c != thiscomment->end(); it_c++) {
        if ((*it_c)->getNo() == num) {
            if ((*it_c)->getuserid() == id) {
                thiscomment->erase(it_c);
                Ncm--;
                (*it_c)->dec();
                QSqlQuery Cquery;
                Cquery.prepare("delete from comment where POSTID = :PID and NO = :NO ");
                Cquery.bindValue(":PID",pid);
                Cquery.bindValue(":NO",num);
                Cquery.exec();
                //如果不是最后一个评论，则调整删除评论的编号
                if(Ncm != 0){
                    Cquery.prepare("update comment set NO = :No where POSTID = :PID and NO = :NO");
                    Cquery.bindValue(":No",(*it_c)->getNo());
                    Cquery.bindValue(":PID",pid);
                    Cquery.bindValue(":NO",(*it_c)->getNo()+1);
                    Cquery.exec();
                    result = 2;	//成功删除
                }
                else
                    return 2;
            }
            else
                return 1;	//不是他的
        } else if(result == 2 && Ncm != 0) {
            (*it_c)->dec();
            //调整删除评论的序号
            QSqlQuery Cquery;
            Cquery.prepare("update comment set NO = :No where POSTID = :PID and NO = :NO");
            Cquery.bindValue(":No",(*it_c)->getNo());
            Cquery.bindValue(":PID",pid);
            Cquery.bindValue(":NO",(*it_c)->getNo()+1);
            Cquery.exec();
        }
    }
    return result;	//没找到
}

QSqlDatabase &operator>>(QSqlDatabase db, map<PostType, vector<Post*> > &tpl)
{
    QSqlQuery Pquery("SELECT*from post");
    PostType dbptype;
    Postptr dbpost;
    iteratorpp dbit;
    while(Pquery.next()) {
        switch (Pquery.value(2).toUInt()) {
        case 0:
            dbptype = Sport;
            break;
        case 1:
            dbptype = Anime;
            break;
        case 2:
            dbptype = Music;
            break;
        case 3:
            dbptype = Movie;
            break;
        case 4:
            dbptype = Game;
            break;
        }
        dbit = tpl.find(dbptype);
        dbpost = new Post(Pquery.value(4).toString().toStdString(),
                          Pquery.value(5).toString().toStdString(),
                          dbptype,
                          Pquery.value(3).toString().toStdString(),
                          Pquery.value(7).toUInt(),
                          Pquery.value(6).toString().toStdString(),
                          Pquery.value(0).toUInt());
        QSqlQuery Cquery("SELECT*from comment");
        //添加评论
        while(Cquery.next()) {
            if(Cquery.value(5).toUInt() == Pquery.value(0).toUInt()) {
                dbpost->addcommet(Cquery.value(3).toString().toStdString(),
                                  Cquery.value(2).toString().toStdString(),
                                  Cquery.value(0).toUInt(),
                                  Cquery.value(4).toString().toStdString(),
                                  Cquery.value(5).toUInt());
            }
        }
        dbit->second.push_back(dbpost);
    }
}

Post::~Post()
{
}
