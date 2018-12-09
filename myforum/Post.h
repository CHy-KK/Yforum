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
	//�������
	void addcommet(string c, string id, int reply);
	//ɾ������
	int deletecomment(int num, string id);
	~Post();

private:
	int PID;
	int number;
	PostType type;      //�����������
	string userid;		//������id
	string title;       //���ӱ���
	string content;     //��������
	string ptime;        //���ӷ���ʱ��
	int Ncm;            //��������������Ŀ
	vector<Commentptr>* thiscomment;    //��������������
}*Postptr;
#endif // !POST_H

