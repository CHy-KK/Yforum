#ifndef COMMENT_H
#define COMMENT_H

#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
#include <QString.h>
#include <QtSql>
enum PostType { Sport, Anime, Music, Movie, Game, Nothing };
using namespace std;

typedef class Comment
{
public:
    Comment();
    Comment(int no, string c, string id, int pid, int r = -1);
    Comment(int no, string c, string id, int r, string time, int pid);
    string getcontent();
    void dec();
    int getNo();
    int getreply();
    int getpid();
    string gettime();
    string getuserid();
    friend ostream &operator<<(ostream &out, Comment *thiscom);
    ~Comment();
private:
    int reply;          //回复楼层，如不是回复设为-1
    int No;             //评论编号
    int PID;            //属于帖子的id
    QString userid;		//评论者id
    QString content;     //评论内容
    string comtime;        //评论发布时间
}*Commentptr ;

#endif // !COMMENT_H
