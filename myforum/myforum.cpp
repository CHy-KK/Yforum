#include "pch.h"
#include <iostream>
#include "data.h"
using namespace std;
vector<Userptr>Userlist;	//用户列表
map<PostType, vector<Postptr> >TotalPostList;    //映射类型总帖子列表，key为板块，value为板块下帖子列表
vector<Postptr>S_PostList;  //运动板块帖子列表,类型为vector<Postptr>
vector<Postptr>A_PostList;  //动漫版块
vector<Postptr>Mu_PostList; //音乐版块
vector<Postptr>Mv_PostList; //电影板块
vector<Postptr>G_PostList;  //游戏板块
long PostID = 10001;
int S_num;
int A_num;
int Mu_num;
int Mv_num;
int G_num;
int main()
{
	TotalPostList.insert(pair<PostType, vector<Postptr> >(Sport, S_PostList));
	TotalPostList.insert(pair<PostType, vector<Postptr> >(Anime, A_PostList));
	TotalPostList.insert(pair<PostType, vector<Postptr> >(Music, Mu_PostList));
	TotalPostList.insert(pair<PostType, vector<Postptr> >(Movie, Mv_PostList));
	TotalPostList.insert(pair<PostType, vector<Postptr> >(Game, G_PostList));
	Administrator administrator1("YCH1", "imadministrator1");
	Administrator administrator2("YCH2", "imadministrator2");
	
	Userptr zss = new normalUser("zss", "zssdhr");
	Userlist.push_back(zss);
	Userptr lmq = new normalUser("lmq", "lmqdhr");
	Userlist.push_back(lmq);
	Userptr zjb = new normalUser("zjb", "zjbdhr");
	Userlist.push_back(zjb);
	Userptr ming = new normalUser("小明", "xiaomingdhr");
	Userlist.push_back(ming);

	Postptr newpptr = new Post("ex1 from zss", "111111111", Sport, "zss");
	TotalPostList.begin()->second.push_back(newpptr);
	newpptr = new Post("ex2 from zss", "222222222", Sport, "zss");
	TotalPostList.begin()->second.push_back(newpptr);

	iteratorpp it_anime = TotalPostList.find(Anime);
	newpptr = new Post("ex3 from lmq", "3333333333", Anime, "lmq");
	it_anime->second.push_back(newpptr);
	newpptr = new Post("有人看过eva吗", "RT", Anime, "zjb");
	it_anime->second.push_back(newpptr);
	newpptr->addcommet("我超喜欢看eva的","lmq",-1);
	newpptr->addcommet("看不懂怎么破", "zjb", 1);
	newpptr->addcommet("看不懂？you are noob", "小明", -1);
	newpptr = new Post("灌水灌水灌水灌水", "灌水就完事了", Anime, "zss");
	it_anime->second.push_back(newpptr);
	newpptr = new Post("其实是为了演示一下翻页功能", "灌水", Anime, "zss");
	it_anime->second.push_back(newpptr);
	newpptr = new Post("还要再灌水两条帖子", "水水水水", Anime, "zss");
	it_anime->second.push_back(newpptr);
	newpptr = new Post("水水水水水水水水水", "水水水水", Anime, "zss");
	it_anime->second.push_back(newpptr);
	newpptr = new Post("水到第二页了！", "水水水水", Anime, "zss");
	it_anime->second.push_back(newpptr);

	iteratorpp it_music = TotalPostList.find(Music);
	newpptr = new Post("ex5 from zss", "5555555555555", Music, "zss");
	it_music->second.push_back(newpptr);
	newpptr = new Post("ex6 from zjb", "66666666666666", Music, "zjb");
	it_music->second.push_back(newpptr);

	iteratorpp it_movie = TotalPostList.find(Movie);
	newpptr = new Post("ex7 from lmq", "777777777777777777", Movie, "lmq");
	it_movie->second.push_back(newpptr);
	newpptr = new Post("ex8 from 小明", "888888888", Movie, "小明");
	it_movie->second.push_back(newpptr);


	iteratorpp it_game = TotalPostList.find(Game);
	newpptr = new Post("我刚用C++的QT写了一个太污绘卷，有人想玩吗", "只要998，太污绘卷带回家", Game, "zss");
	it_game->second.push_back(newpptr);
	newpptr->addcommet("太吾绘卷我玩了，很有意思，你这是个啥玩意儿？", "小明", -1);
	newpptr->addcommet("这是为了演示评论区翻页功能）", "lmq", 1);
	newpptr->addcommet("三楼！", "lmq", 1);
	newpptr->addcommet("四楼！", "lmq", 1);
	newpptr->addcommet("五楼！", "lmq", 1);
	newpptr->addcommet("六楼！", "lmq", 1);
	newpptr->addcommet("七楼！", "lmq", 1);
	newpptr->addcommet("八楼！", "lmq", 1);
	newpptr->addcommet("九楼！", "lmq", 1);
	newpptr->addcommet("十楼！", "lmq", 1);
	newpptr->addcommet("翻页了！", "lmq", 1);
	newpptr->addcommet("翻页x2！", "lmq", 1);
	newpptr->addcommet("翻页x3！", "lmq", 1);
	newpptr->addcommet("翻页x4！", "lmq", 1);
	newpptr->addcommet("演示完毕", "lmq", 1);

	newpptr = new Post("ex10 from 小明", "十十十十十十十十十十", Game, "小明");
	it_game->second.push_back(newpptr);

	bool use = 1;
	State curstate = initial;
	State laststate = initial;
	
	
	string password;
	
	int pagec = 1;			//评论页数
	int pages = 1;
	Userptr thisuser = NULL;
	Administrator* adminuser = NULL;
	Postptr thispost = NULL;
	Administrator admin;
	bool lastpage = 0;		//翻页时是否到达最后一页
	PostType thistype;
	
	while (use) {
		
		if (curstate == initial) {	
			cout << "log in:1; register:0,please input:";
			int choose;
			cin >> choose;
			cin.clear();
			cin.ignore(10000, '\n');
			if (choose == 1)
				curstate = log_in;
			else if (choose == 0)
				curstate = Register;
			else
				MessageBox(NULL, L"状态错误", L"提示", MB_OKCANCEL);
		} 
		else if (curstate == log_in) {
			cout << "administrator log in, enter 1, otherwise enter 2; back to register, enter 3:";
			int ifadministrator;
			cin >> ifadministrator;
			cin.clear();
			cin.ignore(10000, '\n');
			int i = 5;
			bool iflogin = false;
			if (ifadministrator == 1) {
				cout << "please input your id:";
				string id;
				getline(cin, id);
				if (id == administrator1.getUid()) {
					cout << "pleasr input your password:";
					getline(cin, password);
					if (password == administrator1.getpw()) {
						adminuser = &administrator1;
						cout << "login successfully, welcome here " << adminuser->getUid() << "!" << endl;
						curstate = typechoose;
						iflogin = true;
					}
					else
						MessageBox(NULL, L"密码错误", L"提示", MB_OKCANCEL);
				}
				else if (id == administrator2.getUid()) {
					cout << "pleasr input your password:";
					getline(cin, password);
					if (password == administrator2.getpw()) {
						adminuser = &administrator2;
						cout << "login successfully, welcome here " << adminuser->getUid() << "!" << endl;
						curstate = typechoose;
						iflogin = true;
					}
					else
						MessageBox(NULL, L"密码错误", L"提示", MB_OKCANCEL);
				}
				else
					MessageBox(NULL, L"这不是管理员账户！", L"提示", MB_OKCANCEL);
			}
			else if (ifadministrator == 2) {
				cout << "please input your id:";
				string id;
				getline(cin, id);
				thisuser = thisuser->log_in(id);
				if (thisuser != NULL)
					curstate = typechoose;
			}
			else if (ifadministrator == 3)
				curstate = initial;
			else {
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		else if (curstate == Register) {
			string id;
			cout << "please input your id: ";
			getline(cin, id);		//第一次输入id
			bool ifout = false;
			while (true) {
				bool ifused = false;
				for (iteratoru itu = Userlist.begin(); itu != Userlist.end(); itu++) {
					if ((*itu)->getUid() == id) {
						cout << "your id has been used,please change one,or if you want to back to log in, input \"let me go!\"";
						ifused = true;
						getline(cin, id);		//有重复，再次输入
						if (id == "let me go!") {
							curstate = initial;
							ifout = true;
							break;
						}
						break;
					}
				}
				if (ifout)
					break;
				if (!ifused) {
					cout << "please input your password: ";
					getline(cin, password);
					Userptr newuptr = new normalUser(id, password);
					Userlist.push_back(newuptr);
					thisuser = newuptr;
					curstate = typechoose;
					break;
				}
			}
		}
		else if (curstate == typechoose) {
			cout << "please input which type" << endl
				<< "sport1" << endl
				<< "anime:2" << endl
				<< "music:3" << endl
				<< "movie:4" << endl
				<< "game:5" << endl
				<< "now enter your choice: ";
			int ty_ch;
			cin >> ty_ch;
			cin.clear();
			cin.ignore(10000, '\n');
			pages = 1;			//初始在0页
			switch (ty_ch)
			{
			case 1 :
				thistype = Sport;
				curstate = postview;
				break;
			case 2:
				thistype = Anime;
				curstate = postview;
				break;
			case 3:
				thistype = Music;
				curstate = postview;
				break;
			case 4:
				thistype = Movie;
				curstate = postview;
				break;
			case 5:
				thistype = Game;
				curstate = postview;
				break;
			default:
				MessageBox(NULL, L"选择错误，请重新输入", L"提示", MB_OKCANCEL);
			}
		}
		else if (curstate == postview) {
			
			cout << "*********************************************" << endl;
			switch (thistype)
			{
			case Sport:
				cout << "Sport" << " module has " << S_num << " posts now" << endl;
				break;
			case Anime:
				cout << "Anime" << " module has " << A_num << " posts now" << endl;
				break;
			case Music:
				cout << "Music" << " module has " << Mu_num << " posts now" << endl;
				break;
			case Movie:
				cout << "Movie" << " module has " << Mv_num << " posts now" << endl;
				break;
			case Game:
				cout << "Game" << " module has " << G_num << " posts now" << endl;
				break;
			default:
				break;
			}
			cout << "here are the posts, 5 posts per page" << endl;
			iteratorpp it_pp = TotalPostList.find(thistype);
			cout << "now you are in page " << pages << endl;
			cout << endl << "++++++++++++++++++" << endl;

			int index = 0;
			for (iteratorp it_p = it_pp->second.begin(); it_p != it_pp->second.end(); it_p++, index++) {
				if (index == (pages - 1) * 5) {
					int index1 = 1;
					for (iteratorp it_p1 = it_p; it_p1 != it_pp->second.end() && index1 <= 5; index1++, it_p1++) {
						cout << index1 << ": post ID:" << (*it_p1)->getPid() << endl
							<< "Title: " << (*it_p1)->gettitle() << endl
							<< (*it_p1)->getcontent() << endl
							<< (*it_p1)->getuserid() << " add this post in " << (*it_p1)->gettime() << endl
							<< "now has: " << (*it_p1)->getNcm() << " comments" << endl << endl;
					}
				}
			}
			cout << endl << "++++++++++++++++++" << endl;
			cout << "please choose what you want to do next:" << endl
				<< "read post:1" << endl
				<< "next page:2" << endl
				<< "last page:3" << endl
				<< "back to choose type:4" << endl
				<< "log out:5" << endl;
			if (adminuser != NULL) {
				cout << "change normal user's level:6" << endl
					<< "cancel moderator's level:7" << endl
					<< "now enter your choice: ";
				int choice;
				cin >> choice;
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "*********************************************" << endl;
				if (choice == 1) {
					pagec = 1;
					int post_choose;	//选择的帖子id
					cout << "please choose the post you want to read(1——5):";
					cin >> post_choose;
					cin.clear();
					cin.ignore(10000, '\n');
					bool iffind = false;
					for (iteratorp it_p = it_pp->second.begin(); it_p != it_pp->second.end(); it_p++) {
						if ((*it_p)->getPid() == post_choose) {
							curstate = inpost;
							thispost = *it_p;
							iffind = true;
							break;
						}
					}
					if (!iffind)
						MessageBox(NULL, L"该帖子不存在", L"提示", MB_OKCANCEL);
				}
				else if (choice == 2) {

					switch (thistype) {
					case Sport:
						if (S_num / 5 >= pages && S_num % 5 > 0)
							pages++;
						else
							MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
						break;
					case Anime:
						if (A_num / 5 >= pages && A_num % 5 > 0)
							pages++;
						else
							MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
						break;
					case Music:
						if (Mu_num / 5 >= pages && Mu_num % 5 > 0)
							pages++;
						else
							MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
						break;
					case Movie:
						if (Mv_num / 5 >= pages && Mv_num % 5 > 0)
							pages++;
						else
							MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
						break;
					case Game:
						if (G_num / 5 >= pages && G_num % 5 > 0)
							pages++;
						else
							MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
						break;
					default:
						break;
					}
				}
				else if (choice == 3) {
					pages--;
				}
				else if (choice == 4) {
					curstate = typechoose;
				}
				else if (choice == 5) {
					curstate = initial;
					adminuser = adminuser->log_out();
				}
				else if (choice == 6) {
					cout << "input the user id:";//这里还要加一个空格判断
					string id;
					getline(cin, id);
					cout << "input the post type you want to set:" << endl
						<< "sport:1" << endl
						<< "anime:2" << endl
						<< "music:3" << endl
						<< "movie:4" << endl
						<< "game:5" << endl;
					int chan_type;
					PostType pt;
					cin >> chan_type;
					switch (chan_type)
					{
					case 1:
						pt = Sport;
						break;
					case 2:
						pt = Anime;
						break;
					case 3:
						pt = Music;
						break;
					case 4:
						pt = Movie;
						break;
					case 5:
						pt = Game;
						break;
					default:
						break;
					}
					bool ifchange = adminuser->changelevel(id, pt);
					if (!ifchange)
						MessageBox(NULL, L"用户不存在", L"提示", MB_OKCANCEL);
					else
						MessageBox(NULL, L"该用户已成为版主", L"提示", MB_OKCANCEL);
				}
				else if (choice == 7) {
					cout << "input the user id:";
					string id;
					getline(cin, id);
					bool ifcancel = adminuser->cancellevel(id);
					if (!ifcancel)
						MessageBox(NULL, L"该用户不是版主", L"提示", MB_OKCANCEL);
					else
						MessageBox(NULL, L"该用户不再是版主了", L"提示", MB_OKCANCEL);
				}
				else {
					MessageBox(NULL, L"状态错误", L"提示", MB_OKCANCEL);
					cin.clear();
					cin.ignore(10000, '\n');
				}
				continue;
			}
			cout << "your imformation:6" << endl
				<< "add a post:7" << endl
				<< "delete your post:8" << endl;
			
			if (thisuser->getlevel() == 3)
				cout << "change user's level:9" << endl;
			cout << "now enter your choice: ";
			int choice;
			cin >> choice;
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "*********************************************" << endl;
			if (choice == 1) {
				int post_choose;	//选择的帖子id
				cout << "please choose the post you want to read(1——5):";
				cin >> post_choose;
				cin.clear();
				cin.ignore(10000, '\n');
				bool iffind = false;
				for (iteratorp it_p = it_pp->second.begin(); it_p != it_pp->second.end(); it_p++) {
					if ((*it_p)->getPid() == post_choose) {
						curstate = inpost;
						thispost = *it_p;
						iffind = true;
						break;
					}
				}
				if (!iffind)
					MessageBox(NULL, L"无帖子为该id", L"提示", MB_OKCANCEL);
			}
			else if (choice == 2) {
				
				switch (thistype) {
				case Sport:
					if (S_num / 5 >= pages && S_num % 5 > 0)
						pages++;
					else
						MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
					break;
				case Anime:
					if (A_num / 5 >= pages && A_num % 5 > 0)
						pages++;
					else
						MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
					break;
				case Music:
					if (Mu_num / 5 >= pages && Mu_num % 5 > 0)
						pages++;
					else
						MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
					break;
				case Movie:
					if (Mv_num / 5 >= pages && Mv_num % 5 > 0)
						pages++;
					else
						MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
					break;
				case Game:
					if (G_num / 5 >= pages && G_num % 5 > 0)
						pages++;
					else
						MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
					break;
				default:
					break;
				}
			}
			else if (choice == 3) {
				if (pages > 1)
					pages--;
				else
					MessageBox(NULL, L"已经是第一页了", L"提示", MB_OKCANCEL);
			}
			else if (choice == 4) {
				curstate = typechoose;
			}
			else if (choice == 5) {
				thisuser = thisuser->log_out();
				curstate = initial;
			}
			else if (choice == 6) {
				cout << "your id: " << thisuser->getUid() << endl
					<< "your password: " << thisuser->getpw() << endl;
				if (thisuser->getadmin())
					cout << "you are Administrator" << endl;
				else if (thisuser->getlevel())
					switch (thisuser->getmtype())
					{
					case 0:
						cout << "you are moderator in " << "Sport" << endl;
						break;
					case 1:
						cout << "you are moderator in " << "Anime" << endl;
						break;
					case 2:
						cout << "you are moderator in " << "Music" << endl;
						break;
					case 3:
						cout << "you are moderator in " << "Movie" << endl;
						break;
					case 4:
						cout << "you are moderator in " << "Game" << endl;
						break;
					default:
						break;
					}
				else
					cout << "you are a normal user" << endl;	
			}
			else if (choice == 7) {		//	添加帖子
				string C;
				string T;
				cout << "enter the title:";
				getline(cin,T);
				cout << "enter the content:";
				getline(cin, C);
				thisuser->addpost(T, C, thistype, thisuser->getUid(), &it_pp->second);
	
			}
			else if (choice == 8) {		
				cout << "please input the Number of the post you want to delete:1——5" << endl;
				if (thisuser->getlevel() == false)
					cout << "Notice!you can only delete post without comments" << endl;
				int post_del;
				cin >> post_del;
				cin.clear();
				cin.ignore(10000, '\n');
				thisuser->deletepost(&(it_pp->second), thisuser->getUid(), thistype, post_del, thisuser->getmtype());
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				MessageBox(NULL, L"状态错误", L"提示", MB_OKCANCEL);
			}
		}
		else if(curstate == inpost){
			cout << endl << "--------------------------------" << endl;
			cout << "Titlel: " << thispost->gettitle() << endl;
			cout << thispost->getcontent() << endl;
			cout << "now you are in page " << pagec << endl;
			int index = 0;
			for (iteratorc it_c = thispost->getcomment()->begin(); it_c != thispost->getcomment()->end(); it_c++, index++) {
				if (index == (pagec - 1) * 10) {
					int index1 = 1;
					for (iteratorc it_c1 = it_c; it_c1 != thispost->getcomment()->end() && index1 <= 10; index1++, it_c1++) {
						cout << "..........." << endl;
						cout << (*it_c1)->gettime() << ": " << (*it_c1)->getNo() << " floor, username: " << (*it_c1)->getuserid() << endl;
						if ((*it_c1)->getreply() > 0) {
							cout << "reply to " << (*it_c1)->getreply() << " floor: ";
						}
						cout << (*it_c1)->getcontent() << endl << endl;
					}
				}
			}
			cout << "+++++++++++++++++++" << endl;
			cout << "choose what you want to do next:" << endl
				<< "next page:1" << endl
				<< "last page:2" << endl
				<< "back to post list:3" << endl;
			if (adminuser != NULL) {
				int choice;
				cin >> choice;
				cin.clear();
				cin.ignore(10000, '\n');
				if (choice == 1) {
					if (thispost->getNcm() / 10 >= pagec && thispost->getNcm() % 10 > 0)
						pagec++;
					else
						MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
				}
				else if (choice == 2) {
					if (pagec > 1)
						pagec--;
					else
						MessageBox(NULL, L"已经是第一页了", L"提示", MB_OKCANCEL);
				}
				else if (choice == 3) {
					curstate = postview;
				}
				else {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "wrong state!" << endl;
				}
				continue;
			}
			cout << "add comment4" << endl
				<< "delete commet5" << endl
				<< "now enter your choice: ";
			int choice;
			cin >> choice;
			if (choice == 1) {
				if (thispost->getNcm() / 10 >= pagec && thispost->getNcm() % 10 > 0)
					pagec++;
				else
					MessageBox(NULL, L"已经是最后一页了", L"提示", MB_OKCANCEL);
			}
			else if (choice == 2) {
				if (pagec > 1) 
					pagec--;
				else
					MessageBox(NULL, L"已经是第一页了", L"提示", MB_OKCANCEL);
			}
			else if (choice == 3) {
				curstate = postview;
			}
			else if (choice == 4) {
				cout << "if you want to reply to one user, please enter the Number, otherwise whatever you want: ";
				int replyNo;
				cin >> replyNo;
				cin.clear();
				cin.ignore(10000, '\n');

				while (replyNo != -1 && (replyNo < 1 || replyNo > thispost->getNcm())) {
					MessageBox(NULL, L"该评论不存在！请重新输入", L"提示", MB_OKCANCEL);
					cin >> replyNo;
					cin.clear();
					cin.ignore(10000, '\n');
				}
				cout << "enter your comment: ";
				string com;	
				getline(cin, com);
				thispost->addcommet(com, thisuser->getUid(), replyNo);
			}
			else if (choice == 5) {
				cout << "enter the number of comment you want to delete" << endl
					<< "Notice! you can only delete your own comment!" << endl
					<< "now enter the number: ";	
				int deleteNo;
				cin >> deleteNo;
				cin.clear();
				cin.ignore(10000, '\n');
				int ifdelete = thispost->deletecomment(deleteNo, thisuser->getUid());
				if (ifdelete == 0)
					MessageBox(NULL, L"没有这个评论", L"提示", MB_OKCANCEL);
				else if (ifdelete == 1)
					MessageBox(NULL, L"这不是你的评论！", L"提示", MB_OKCANCEL);
				else
					MessageBox(NULL, L"成功删除", L"提示", MB_OKCANCEL);
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				MessageBox(NULL, L"状态错误", L"提示", MB_OKCANCEL);
			}
		}
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
