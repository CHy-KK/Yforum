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
normalUser::normalUser()
{

}
normalUser::normalUser(string id, string pw, bool l, PostType pt)
{
	ID = id;
	password = pw;
	level = l;
	Modertype = Nothing;
	ifadmin = false;
}

normalUser* normalUser::log_in(string id)
{
	for (iteratoru itu = Userlist.begin(); itu != Userlist.end(); itu++) {
		if ((*itu)->getUid() == id) {
			int i = 5;
			while (i) {
				cout << "pleasr input your password:";
				string password;
				getline(cin, password);
				if (password == (*itu)->getpw()) {
					cout << "login successfully, welcome here " << id << "!" << endl;
					return *itu;
				}
				MessageBox(NULL, L"������������������5��", L"��ʾ", MB_OKCANCEL);
				i--;
			}
			if (!i) {
				MessageBox(NULL, L"������󣡷��س�ʼ״̬", L"��ʾ", MB_OKCANCEL);
				return NULL;
			}
		}
	}
	MessageBox(NULL, L"�˺Ų�����", L"��ʾ", MB_OKCANCEL);
	return NULL;
}

normalUser * normalUser::log_out()
{
	return NULL;
}

void normalUser::addpost(string T, string C, PostType thistype, string uid, vector<Postptr>* head)
{
	Postptr newpptr = new Post(T, C, thistype, uid);
	head->push_back(newpptr);
	if (head->begin() != head->end()) {
		cout << newpptr->gettitle() << endl;
		cout << newpptr->getcontent() << endl;
	}
}

void normalUser::changeid(string newid) {
	ID = newid;
}

void normalUser::changepw(string newpw) {
	password = newpw;
}

void normalUser::deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype)
{
	for (iteratorp it = head->begin(); it != head->end(); it++) {  //ʹ�õ�����it��������µ������б�
		if ((*it)->getPid() == post_del) {
			if ((*it)->getuserid() == uid && (*it)->getNcm() == 0) {
				head->erase(it);
				MessageBox(NULL, L"ɾ���ɹ���", L"��ʾ", MB_OKCANCEL);
				return;
			}
			else {
				if ((*it)->getuserid() != uid)
					MessageBox(NULL, L"�ⲻ��������ӣ��㲻��ɾ��", L"��ʾ", MB_OKCANCEL);
				else
					MessageBox(NULL, L"���������ۣ��޷�ɾ��", L"��ʾ", MB_OKCANCEL);
				return;
			}
		}
	}
}

void normalUser::setmtype(PostType pt) {
	Modertype = pt;
}

void Moderator::deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype)
{
	for (iteratorp it = head->begin(); it != head->end(); it++) {  //ʹ�õ�����it��������µ������б�
		if ((*it)->getPid() == post_del) {
			if ((thistype == mtype) || ((*it)->getuserid() == uid && (*it)->getNcm() == 0)) {
				head->erase(it);
				MessageBox(NULL, L"ɾ���ɹ���", L"��ʾ", MB_OKCANCEL);
				return;
			}
			else {
				MessageBox(NULL, L"�㲻�ܹ������ģ��", L"��ʾ", MB_OKCANCEL);
				break;
			}
		}
	}
}

void Moderator::disablemtype()
{
	Modertype = Nothing;
}

void Moderator::disablelevel()
{
	level = false;
}

Moderator::~Moderator()
{
}

normalUser::~normalUser()
{
}

bool Administrator::changelevel(string uid, PostType pt)
{
	for (iteratoru it_u = Userlist.begin(); it_u != Userlist.end(); it_u++) {
		if ((*it_u)->getUid() == uid) {
			normalUser* newmor = (normalUser*)new Moderator();
			*newmor = *(*it_u);
			newmor->enablelevel();
			newmor->setmtype(pt);
			Userlist.erase(it_u);
			Userlist.push_back(newmor);
			return true;
		}
	}
	return false;
}

bool Administrator::cancellevel(string uid)
{
	for (iteratoru it_u = Userlist.begin(); it_u != Userlist.end(); it_u++) {
		if ((*it_u)->getUid() == uid) {
			Userptr newuser = new normalUser;
			*newuser = *(*it_u);
			newuser->disablelevel();
			newuser->disablemtype();
			Userlist.erase(it_u);
			Userlist.push_back(newuser);
			return true;
		}
	}
	return false;
}

