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

Post::Post()
{

}

Post::Post(string t, string c, PostType tp, string uid, int n) {
	PID = PostID;
	PostID++;
	title = t;
	content = c;
	Ncm = n;

	const time_t nowtime = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A", localtime(&nowtime));
	ptime = (string)tmp;

	type = tp;
	userid = uid;
	thiscomment = new Commentlist;
	switch (type)
	{
	case Sport:
		number = ++S_num;
		break;
	case Anime:
		number = ++A_num;
		break;
	case Music:
		number = ++Mu_num;
		break;
	case Movie:
		number = ++Mv_num;
		break;
	case Game:
		number = ++G_num;
		break;
	default:
		break;
	}
}

int Post::getPid() {
	return PID;
}

int Post::getnumber() {
	return number;
}

int Post::getNcm()
{
	return Ncm;
}

string Post::getuserid()
{
	return userid;
}

string Post::gettitle() {
	return title;
}

string Post::getcontent() {
	return content;
}

string Post::gettime() {
	return ptime;
}

void Post::setNcm()
{
	Ncm++;
}

vector<Commentptr>* Post::getcomment() {
	return thiscomment;
}

void Post::addcommet(string c, string id, int reply)
{
	Commentptr newcom = new Comment(++Ncm, c, id, reply);
	thiscomment->push_back(newcom);
}

int Post::deletecomment(int num, string id) 
{
	for (iteratorc it_c = thiscomment->begin(); it_c != thiscomment->end(); it_c++) {
		if ((*it_c)->getNo() == num) {
			if ((*it_c)->getuserid() == id) {
				thiscomment->erase(it_c);
				Ncm--;
				return 2;	//�ɹ�ɾ��
			}
			else
				return 1;	//��������
		}
	}
	return 0;	//û�ҵ�
}

Post::~Post()
{
}
