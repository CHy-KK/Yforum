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
normalUser::normalUser()
{

}
normalUser::normalUser(string id, string pw, bool l, PostType pt)
{
    ID = QString::fromStdString(id);
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
                MessageBox(NULL, L"密码错误！你最多可以输错5次", L"提示", MB_OKCANCEL);
                i--;
            }
            if (!i) {
                MessageBox(NULL, L"密码错误！返回初始状态", L"提示", MB_OKCANCEL);
                return NULL;
            }
        }
    }
    MessageBox(NULL, L"账号不存在", L"提示", MB_OKCANCEL);
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
    cout<<newpptr;
}

void normalUser::changeid(string newid) {
    ID = QString::fromStdString(newid); ;
}

void normalUser::changepw(string newpw) {
    password = newpw;
}

void normalUser::deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype)
{
    for (iteratorp it = head->begin(); it != head->end(); it++) {  //使用迭代器it遍历板块下的帖子列表
        if ((*it)->getPid() == post_del) {
            if ((*it)->getuserid() == uid && (*it)->getNcm() == 0) {
                head->erase(it);
                //在数据库中删除该帖
                QSqlQuery Pquery;
                Pquery.prepare("delete from post where PID = :PID");
                Pquery.bindValue(":PID",post_del);
                Pquery.exec();
                //在数据库中删除该帖评论
                QSqlQuery Cquery;
                Cquery.prepare("delete from comment where POSTID = :PID");
                Cquery.bindValue(":PID",post_del);
                Cquery.exec();
                MessageBox(NULL, L"删除成功！", L"提示", MB_OKCANCEL);
                return;
            }
            else {
                if ((*it)->getuserid() != uid)
                    MessageBox(NULL, L"这不是你的帖子，你不能删除", L"提示", MB_OKCANCEL);
                else
                    MessageBox(NULL, L"该帖有评论，无法删除", L"提示", MB_OKCANCEL);
                return;
            }
        }
    }
}

void normalUser::setmtype(PostType pt) {
    Modertype = pt;
}

QSqlDatabase &operator >>(QSqlDatabase db, vector<normalUser*> & ul)
{
    Userptr dbuser;
    QSqlQuery Uquery("SELECT*from user");
    PostType dbptype;
    while(Uquery.next()) {
        if(Uquery.value(2).toBool()) {
            cout<<"in"<<endl;
            switch (Uquery.value(4).toUInt()) {
            case 0:
                dbptype = Sport;
                break;
            case 1:
                dbptype = Anime;
                break;
            case 2:
                dbptype = Music;
                break;
            case 3:
                dbptype = Movie;
                break;
            case 4:
                dbptype = Game;
                break;
            }
            cout<<Uquery.value(2).toBool()<<endl;
            dbuser = (normalUser*)new Moderator(Uquery.value(0).toString().toStdString(),
                                                Uquery.value(1).toString().toStdString(),
                                                Uquery.value(2).toBool(), dbptype);
        }
        else
            dbuser = new normalUser(Uquery.value(0).toString().toStdString(),
                                Uquery.value(1).toString().toStdString());
        ul.push_back(dbuser);
    }
    for (iteratoru itu = ul.begin(); itu != ul.end(); itu++) {
        cout<<(*itu)->getUid() << " "<< (*itu)->getpw() << " " << (*itu)->getlevel() << endl;
    }
}

Moderator::Moderator() {

}

Moderator::Moderator(string id, string pw, bool l, PostType pt) {
    ID = QString::fromStdString(id);
    password = pw;
    level = l;
    Modertype = pt;
    ifadmin = false;
}

void Moderator::deletepost(vector<Postptr>* head, string uid, PostType thistype, int post_del, PostType mtype)
{
    for (iteratorp it = head->begin(); it != head->end(); it++) {  //使用迭代器it遍历板块下的帖子列表
        if ((*it)->getPid() == post_del) {
            if ((thistype == mtype) || ((*it)->getuserid() == uid && (*it)->getNcm() == 0)) {
                head->erase(it);
                //在数据库中删除该帖
                QSqlQuery Pquery;
                Pquery.prepare("delete from post where PID = :PID");
                Pquery.bindValue(":PID",post_del);
                Pquery.exec();
                //在数据库中删除该帖评论
                QSqlQuery Cquery;
                Cquery.prepare("delete from comment where POSTID = :PID");
                Cquery.bindValue(":PID",post_del);
                Cquery.exec();
                MessageBox(NULL, L"删除成功！", L"提示", MB_OKCANCEL);
                return;
            }
            else {
                MessageBox(NULL, L"你不能管理这个模块或该帖有评论你无法删除", L"提示", MB_OKCANCEL);
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
            //在数据库中删除该帖
            int ptype;
            switch (pt) {
            case Sport:
                ptype = 0;
                break;
            case Anime:
                ptype = 1;
                break;
            case Music:
                ptype = 2;
                break;
            case Movie:
                ptype = 3;
                break;
            case Game:
                ptype = 4;
                break;
            default:
                break;
            }

            QSqlQuery Uquery;
            Uquery.prepare("update user set LEVEL = 1 where ID = :ID");
            Uquery.bindValue(":ID",QString::fromStdString(uid));
            Uquery.exec();
            Uquery.prepare("update user set POSTTYPE = :type where ID = :ID");
            Uquery.bindValue(":ID",QString::fromStdString(uid));
            Uquery.bindValue(":type",ptype);
            Uquery.exec();
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
            QSqlQuery Uquery;
            Uquery.prepare("update user set LEVEL = 0 where ID = :ID");
            Uquery.bindValue(":ID",QString::fromStdString(uid));
            Uquery.exec();
            return true;
        }
    }
    return false;
}

