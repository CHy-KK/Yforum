#ifndef USER_H
#define USER_H
#include "baseuser.h"

typedef class normalUser: public User
{
public:
    normalUser();
    normalUser(string id, string pw, bool l = false, PostType pt = Nothing);
    //登陆
    string log_in(string id);
    //登出
    normalUser* log_out();
    //添加一个帖子,同时添加到自己的list和全局的帖子列表内
    void addpost(string T, string C, PostType thistype, string uid, vector<Postptr>* head);
    //更改用户名
    void changeid(string newid);
    //更改密码
    void changepw(string newpw);
    //删除帖子
    virtual void deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype = Nothing);
    //设置管理板块
    void setmtype(PostType pt);
    //取消管理模块
    virtual void disablemtype() {}
    //取消版主权限
    virtual void disablelevel() {}
    //重载>>从数据库导入内存
    friend QSqlDatabase&operator >>(QSqlDatabase db, vector<normalUser*> & ul);

    ~normalUser();

}*Userptr;

class Moderator : public normalUser
{
public:
    Moderator();
    Moderator(string id, string pw, bool l, PostType pt);
    //版主删帖
    virtual void deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype);
    //撤销管理板块
    virtual void disablemtype();
    //取消版主权限
    virtual void disablelevel();
    ~Moderator();
};

class Administrator : public User
{
public:
    Administrator() {
        ifadmin = true;
    }
    Administrator(string id, string pw) {
        ID = QString::fromStdString(id); ;
        password = pw;
    }
    Administrator* log_out() {
        return NULL;
    }
    bool changelevel(string uid, PostType pt);
    bool cancellevel(string uid);
    bool getadmin() {
        return ifadmin;
    }
    ~Administrator() {};

};

#endif
