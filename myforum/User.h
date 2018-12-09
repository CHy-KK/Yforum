#pragma once
#ifndef USER_H
#define USER_H
#include "Application.h"

typedef class normalUser: public User
{
public:
	normalUser();
	normalUser(string id, string pw, bool l = false, PostType pt = Nothing);
	//��½
	normalUser* log_in(string id);
	//�ǳ�
	normalUser* log_out();
	//���һ������,ͬʱ��ӵ��Լ���list��ȫ�ֵ������б���
	void addpost(string T, string C, PostType thistype, string uid, vector<Postptr>* head);
	//�����û���
	void changeid(string newid);
	//��������
	void changepw(string newpw);
	//ɾ������
	virtual void deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype = Nothing);
	//���ù�����
	void setmtype(PostType pt);
	//ȡ������ģ��
	virtual void disablemtype() {}
	//ȡ������Ȩ��
	virtual void disablelevel() {}
	~normalUser();
	
}*Userptr;

class Moderator : public normalUser
{
public:
	//Moderator(const normalUser & obj);
	//����ɾ��
	virtual void deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype);
	//����������
	virtual void disablemtype();
	//ȡ������Ȩ��
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
		ID = id;
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




#endif // !1
