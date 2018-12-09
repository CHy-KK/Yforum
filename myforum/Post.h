#pragma once
#ifndef POST_H
#define POST_H
#include "comment.h"
typedef class Post
{
public:
	Post();
	Post(string t, string c, PostType tp, string uid, int n = 0);
	int getPid();
	int getnumber();
	int getNcm();
	string getuserid();
	string gettitle();
	string getcontent();
	string gettime();
	void setNcm();
	vector<Commentptr>* getcomment();
	//添加评论
	void addcommet(string c, string id, int reply);
	//删除评论
	int deletecomment(int num, string id);
	~Post();

private:
	int PID;
	int number;
	PostType type;      //帖子所属板块
	string userid;		//发帖人id
	string title;       //帖子标题
	string content;     //帖子内容
	string ptime;        //帖子发布时间
	int Ncm;            //该帖子下评论数目
	vector<Commentptr>* thiscomment;    //帖子下评论数组
}*Postptr;
#endif // !POST_H

