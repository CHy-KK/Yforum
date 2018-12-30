#ifndef POST_H
#define POST_H
#include "comment.h"
typedef class Post
{
public:
    Post();
    Post(string t, string c, PostType tp, string uid, int n = 0);
    Post(string t, string c, PostType tp, string uid, int n, string time, int pid);
    int getPid();
    int getnumber();
    int getNcm();
    int gettype();
    string getuserid();
    string gettitle();
    string getcontent();
    string gettime();
    void setNcm();
    vector<Commentptr>* getcomment();
    //添加评论
    void addcommet(string c, string id, int reply, string time, int pid);
    void addcommet(string c, string id, int reply, int PID);
    //删除评论
    int deletecomment(int num, string id, int pid);

    friend QSqlDatabase & operator>>(QSqlDatabase db, map<PostType, vector<Post*> > & tpl);

    friend ostream & operator<<(ostream &out,Post *thispost);

    ~Post();

private:
    int PID;
    int number;
    PostType type;      //帖子所属板块
    QString userid;		//发帖人id
    QString title;       //帖子标题
    QString content;     //帖子内容
    string ptime;        //帖子发布时间
    int Ncm;            //该帖子下评论数目
    vector<Commentptr>* thiscomment;    //帖子下评论数组
}*Postptr;
#endif // !POST_H

