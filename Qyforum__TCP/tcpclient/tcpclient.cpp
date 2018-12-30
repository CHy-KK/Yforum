#include "tcpclient.h"

std::string e_to_str(PostType t){
    switch (t) {
    case Sport:
        return "sport";
    case Anime:
        return "anime";
    case Music:
        return "music";
    case Movie:
        return "movie";
    case Game:
        return "Game";
    }
}

tcpclient::tcpclient() : QObject(nullptr)
{

}

std::string tcpclient::getmessage()
{
    return message;
}

void tcpclient::start_read()
{
    tcpSocket = new QTcpSocket(this);
    tcpclient::newConnect("localhost",6666);

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}

void tcpclient::readMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_6);
    in >> Qmessage;
    std::string tempmessage;
    tempmessage = Qmessage.toStdString();
    tcpSocket->close();
    //std::cout<<"message1 is : "<<tempmessage<<std::endl;

    //根据接受到数据种类来激活不同信号以及对字符串的解析
    std::string me_type = tempmessage.substr(0,tempmessage.find_first_of(';'));
    //std::cout<<"type is "<<me_type<<endl;
    if(me_type == "login") {
        message = tempmessage.substr(tempmessage.find_first_of(';') + 1);
        std::cout<<"message2 is : "<<message<<endl;
        emit goto_login();
    } else if (me_type == "level") {
        int pos = tempmessage.find_last_of(';') + 1;
        std::string type_str = tempmessage.substr(pos,pos);
        int type = std::stoi(type_str);
        emit goto_level(type);
    } else if (me_type == "postlist") {
        message = tempmessage.substr(tempmessage.find_first_of(';') + 1);
        thisuser->postlist = message;
        std::cout << std::endl << message << std::endl;  //  这不是测试输出！
        emit postview();
    } else if(me_type == "choosepost") {
        message = tempmessage.substr(tempmessage.find_first_of(';') + 1);
        if(message != "nopost") {
            thisuser->commentlist = message;
            std::cout << std::endl << message << std::endl;
            emit inpost();
        } else {
            std::cout << thisuser->postlist;
            MessageBox(NULL, L"该帖子不存在！", L"提示", MB_OKCANCEL);
            state_postview();
        }

    }
}

void tcpclient::newConnect(std::string a, int b)
{
    tcpSocket->abort(); //取消已有的连接
    tcpSocket->connectToHost(QString::fromStdString(a),b);
}
/*
 *
 *
 * 发送部分
 *
 *
*/

void tcpclient::start_send(Symbol s, std::string m)
{
    switch(s){
    case LOGIN:
        uid = m;
        message = "login;" + m;
        std::cout<<"in login"<<std::endl;
        break;
    case LEVEL:
        message = "level;";
        std::cout<<"in level"<<std::endl;
        break;
    case POSTLIST:
        message = "postlist;" + e_to_str(thisuser->curtype);
        break;
    case CHOOSEPOST:
        message = "choosepost;" + m;
        break;
    }

    tcpSocket = new QTcpSocket(this);
    tcpSocket->abort(); //取消已有的连接
    tcpclient::newConnect("localhost",6666);
    //连接信号和相应槽函数
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(sendMessage()));
}

void tcpclient::sendMessage()
{
    QByteArray block;
    std::cout<<"client send "<<message<<std::endl;
    QDataStream out(&block,QIODevice::WriteOnly);
    const char* m = message.c_str();
    out.setVersion(QDataStream::Qt_4_6);
    out<<QObject::tr(m);
    tcpSocket->write(block);
    tcpSocket->close();

    //发送数据成功后，显示提示
    std::cout<<"client send message successful!!!"<<endl;
    start_read();
}

void tcpclient::state_initial()
{
    std::cout << "visitor:2;    log in:1;    register:0,please input:";
    int choose;
    std::cin >> choose;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    if (choose == 1)
        emit log_in();
    else if (choose == 0)
        emit Register();
    else if (choose == 2){
        emit typechoose();
        visitor = true;
    }
    else {
        MessageBox(NULL, L"状态错误", L"提示", MB_OKCANCEL);
        state_initial();
    }
}

void tcpclient::state_login()
{
    std::string id;
    std::cout<<"please enter your id: ";

    std::getline(std::cin, id);
    thisuser->log_in(id);
}

void tcpclient::state_typechoose()
{
    std::cout <<"in typechoose"<<std::endl;
    std::cout << "please input which type" << std::endl
        << "sport1" << std::endl
        << "anime:2" << std::endl
        << "music:3" << std::endl
        << "movie:4" << std::endl
        << "game:5" << std::endl
        << "now enter your choice: ";
    int ty_ch;
    std::cin >> ty_ch;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    switch (ty_ch)
    {
    case 1:
        thisuser->curtype = Sport;
        break;
    case 2:
        thisuser->curtype = Anime;
        break;
    case 3:
        thisuser->curtype = Music;
        break;
    case 4:
        thisuser->curtype = Movie;
        break;
    case 5:
        thisuser->curtype = Game;
        break;
    default:
        MessageBox(NULL, L"选择错误，请重新输入", L"提示", MB_OKCANCEL);
    }
    start_send(POSTLIST);
}

void tcpclient::state_postview()
{
    std::cout << std::endl << "++++++++++++++++++" << std::endl
        << "please choose what you want to do next:" << std::endl
        << "read post:1" << std::endl
        << "back to choose type:2" << std::endl
        << "log out:3" << std::endl;
    //游客或者管理员
    if (thisuser->getadmin() == 1 || visitor) {
        if (!visitor) {
            std::cout << "change normal user's level:4" << std::endl
                << "cancel moderator's level:5" << std::endl;
        }

    } else {
        std::cout << "add a post:4" << std::endl
                  << "delete a post:5" << std::endl
                  << "your information:6" << std::endl;
    }
    std::cout << "now enter your choice: ";
    int choice;
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "*********************************************" << std::endl;
    if(choice == 1){
        if(message != "no post") {
            int post_choose;	//选择的帖子id
            std::cout << "please choose the post you want to read(1-5):";
            std::cin >> post_choose;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            start_send(CHOOSEPOST,std::to_string(post_choose));
        }
        else {
            MessageBox(NULL, L"无帖子！", L"提示", MB_OKCANCEL);
            emit postview();
        }
    } else if(choice == 2) emit typechoose();
    else if(choice == 3) emit log_in();
    else if(choice == 6 && !(thisuser->getadmin() || visitor)) {
        std::cout << thisuser->postlist;
        std::cout << ">>>>>>>>>>>>>>>>>\nyour id: " << thisuser->getUid() << std::endl
                  << "your password: " << thisuser->getpw() << std::endl;
        std::cout << "<<<<<<<<<<<<<<<<<\n";
        if(thisuser->getlevel()) {
            switch (thisuser->getmtype())
            {
            case 0:
                std::cout << "you are moderator in " << "Sport" << std::endl;
                break;
            case 1:
                std::cout << "you are moderator in " << "Anime" << std::endl;
                break;
            case 2:
                std::cout << "you are moderator in " << "Music" << std::endl;
                break;
            case 3:
                std::cout << "you are moderator in " << "Movie" << std::endl;
                break;
            case 4:
                std::cout << "you are moderator in " << "Game" << std::endl;
                break;
            default:
                break;
            }
        }

        state_postview();
    }
    else {
        MessageBox(NULL, L"状态错误！", L"提示", MB_OKCANCEL);
        std::cout << thisuser->postlist;
        state_postview();
    }

}

void tcpclient::state_inpost()
{
    std::cout << "+++++++++++++++++++" << std::endl;
    std::cout << "choose what you want to do next:" << std::endl
        << "back to post list:1" << std::endl;
    int choice;
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    if(choice == 1) {
        std::cout << thisuser->postlist;
        emit postview();
    }
    else {
        MessageBox(NULL, L"状态错误！", L"提示", MB_OKCANCEL);
        std::cout << thisuser->commentlist;
        state_inpost();
    }

}

void tcpclient::login_2()
{
    std::cout<<"login_2"<<std::endl;
    if(message != "unsuccessful"){
        //如果是密码，返回字符串开头加一个;
        std::string pw = message.substr(1);
        int i = 5;
        while (i) {
            std::cout << "pleasr input your password:";
            std::string temppassword;
            std::getline(std::cin, temppassword);
            if (temppassword == pw) {
                std::cout << "login successfully, welcome here "<< uid << "!" << std::endl;
                //创建一个用户指针，并返回
                upw = temppassword;
                start_send(LEVEL);
                connect(this,SIGNAL(goto_level(int)),this,SLOT(login_3(int)));
                return;
            }
            MessageBox(NULL, L"密码错误！你最多可以输错5次", L"提示", MB_OKCANCEL);
            i--;
        }
        if (!i) {
            MessageBox(NULL, L"密码错误！返回初始状态", L"提示", MB_OKCANCEL);

        }
    }
    MessageBox(NULL, L"账号不存在", L"提示", MB_OKCANCEL);
}

void tcpclient::login_3(int temptype)
{
    PostType ptype;
    if(temptype == -1){   //服务端应返回确切数值，如果没有等级返回字符串-1
        thisuser = new normalUser(uid,upw);
    } else {

        switch (temptype) {
        case 0:
            ptype = Sport;
            break;
        case 1:
            ptype = Anime;
            break;
        case 2:
            ptype = Music;
            break;
        case 3:
            ptype = Movie;
            break;
        case 4:
            ptype = Game;
            break;
        }
        thisuser = (normalUser*)new Moderator(uid,upw,true,ptype);
    }

    std::cout<<thisuser->getUid()<<std::endl
            <<thisuser->getpw()<<std::endl;
    if(thisuser->getlevel()) {
        std::cout<<thisuser->getlevel()<<std::endl
                <<thisuser->getmtype()<<std::endl;
    }
    emit typechoose();
}
