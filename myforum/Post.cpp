#include "pch.h"
#include "data.h"
extern vector<Userptr>Userlist;	//用户列表
extern map<PostType, vector<Postptr> >TotalPostList;    //映射类型总帖子列表，key为板块，value为板块下帖子列表
extern vector<Postptr>S_PostList;  //运动板块帖子列表,类型为vector<Postptr>
extern vector<Postptr>A_PostList;  //动漫版块
extern vector<Postptr>Mu_PostList; //音乐版块
extern vector<Postptr>Mv_PostList; //电影板块
extern vector<Postptr>G_PostList;  //游戏板块
extern long PostID;         //帖子id
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
				return 2;	//成功删除
			}
			else
				return 1;	//不是他的
		}
	}
	return 0;	//没找到
}

Post::~Post()
{
}
