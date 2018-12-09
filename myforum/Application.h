#pragma once
#ifndef  APPLICATION_H
#define APPLICATION_H	//	�ļ��������������
#include "Post.h"

class User
{
public:
	User() {};
	//��ȡ�û�id
	string getUid(){
		return ID;
	}
	//��ȡ�û�����
    string getpw() {
		return password;
	}
	//��ȡ�û�Ȩ�޵ȼ�
	int getlevel() {
		return level;
	}
	//��ȡ������
	PostType getmtype() {
		return Modertype;
	}
	//�鿴�Լ���������
	vector<Post> getposts() {
		return postlist;
	}
	//�����û�Ϊ����
	void enablelevel() {
		level = true;
	}
	//��֪�û��Ƿ��ǹ���Ա
	bool getadmin() {
		return ifadmin;
	}
	~User() {};
protected:
	string ID;              //�û���
	string password;        //�û�����
	bool level;				//�û��ȼ���0����ͨ��1������
	bool ifadmin;

	PostType Modertype;
	vector<Post>postlist;	//�û����������б�

};

#endif // ! MODERATOR_H