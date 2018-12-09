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
	int reply;          //�ظ�¥�㣬�粻�ǻظ���Ϊ-1
	int No;             //���۱��
	string userid;		//������id
	string content;     //��������
	string comtime;        //���۷���ʱ��
}*Commentptr ;
	    
#endif // !COMMENT_H