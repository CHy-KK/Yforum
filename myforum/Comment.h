#pragma once
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

enum PostType { Sport, Anime, Music, Movie, Game, Nothing };
using namespace std;

typedef class Comment
{
public:
	Comment();
	Comment(int no, string c, string id, int r = -1);
	string getcontent();
	int getNo();
	int getreply();
	string gettime();
	string getuserid();
	~Comment();
private:
	int reply;          //回复楼层，如不是回复设为-1
	int No;             //评论编号
	string userid;		//评论者id
	string content;     //评论内容
	string comtime;        //评论发布时间
}*Commentptr ;
	    
#endif // !COMMENT_H