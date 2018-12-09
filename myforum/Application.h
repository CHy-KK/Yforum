#pragma once
#ifndef  APPLICATION_H
#define APPLICATION_H	//	文件名打错了嘤嘤嘤
#include "Post.h"

class User
{
public:
	User() {};
	//获取用户id
	string getUid(){
		return ID;
	}
	//获取用户密码
    string getpw() {
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
	//查看自己发的帖子
	vector<Post> getposts() {
		return postlist;
	}
	//设置用户为版主
	void enablelevel() {
		level = true;
	}
	//获知用户是否是管理员
	bool getadmin() {
		return ifadmin;
	}
	~User() {};
protected:
	string ID;              //用户名
	string password;        //用户密码
	bool level;				//用户等级，0：普通，1：版主
	bool ifadmin;

	PostType Modertype;
	vector<Post>postlist;	//用户发的帖子列表

};

#endif // ! MODERATOR_H