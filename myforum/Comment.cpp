#include "pch.h"
#include "data.h"
extern vector<Userptr>Userlist;	//�û��б�
extern map<PostType, vector<Postptr> >TotalPostList;    //ӳ�������������б�keyΪ��飬valueΪ����������б�
extern vector<Postptr>S_PostList;  //�˶���������б�,����Ϊvector<Postptr>
extern vector<Postptr>A_PostList;  //�������
extern vector<Postptr>Mu_PostList; //���ְ��
extern vector<Postptr>Mv_PostList; //��Ӱ���
extern vector<Postptr>G_PostList;  //��Ϸ���
extern long PostID;         //����id
extern int S_num;
extern int A_num;
extern int Mu_num;
extern int Mv_num;
extern int G_num;
Comment::Comment()
{
}
Comment::Comment(int no, string c, string id, int r)
{
	No = no;
	content = c;
	reply = r;
	userid = id;
	const time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A", localtime(&t));
	comtime = (string)tmp;
}


string Comment::getcontent() {
	return content;
}

int Comment::getNo()
{
	return No;
}

int Comment::getreply()
{
	return reply;
}

string Comment::gettime()
{
	return comtime;
}

string Comment::getuserid()
{
	return userid;
}

Comment::~Comment()
{
}

