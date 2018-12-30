#ifndef BASEUSER_H
#define BASEUSER_H

#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
#include <QString.h>

enum PostType { Sport, Anime, Music, Movie, Game, Nothing };
//enum State {  };

class User
{
public:
    PostType curtype;
    std::string postlist;
    std::string commentlist;
    User()
    {
    }
    //获取用户id
    std::string getUid(){
        return ID.toStdString();
    }
    //获取用户密码
    std::string getpw() {
        return password;
    }
    //获取用户权限等级
    int getlevel() {
        return level;
    }
    //获取管理板块
    PostType getmtype() {
        return Modertype;
    }
    //设置用户为版主
    void enablelevel() {
        level = true;
    }
    //获知用户是否是管理员
    bool getadmin() {
        return ifadmin;
    }
protected:
    QString ID;              //用户名
    std::string  password;        //用户密码
    bool level;				//用户等级，0：普通，1：版主
    bool ifadmin;

    PostType Modertype;

};

#endif // BASEUSER_H
