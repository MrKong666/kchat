#ifndef GLOBAL_H
#define GLOBAL_H
#include<QWidget>
#include<functional>
#include"QStyle"
#include<QRegularExpression>
#include<iostream>
#include<memory>
#include<mutex>
#include<QByteArray>
#include<QNetworkReply>
#include<QJsonObject>
#include<QDir>
#include<QSettings>
//用来刷新qss
/*extern 关键字起到了**声明（Declaration）而非定义（Definition）**的作用。
简单来说，它的核心作用是：告诉编译器这个变量在其他地方已经定义过了，现在只是在这里“打个招呼”，以便当前文件可以使用它。*/
extern std::function<void(QWidget*)> repolish;

enum ReqId{
    ID_GET_VARIFY_CODE=1001,//获取验证码
    ID_REG_USER=1002,//注册用户
};
enum Modules{
    REGISTERMOD=0,
};
enum ErrorCodes{
    SUCCESS=0,
    ERR_HSON=1,//json解析失败
    ERR_NETWORK=2,//网络错误
};
extern QString gate_url_prefix;
#endif // GLOBAL_H
