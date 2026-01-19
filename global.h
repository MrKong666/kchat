#ifndef GLOBAL_H
#define GLOBAL_H
#include<QWidget>
#include<functional>
#include"QStyle"
#include<QRegularExpression>
//用来刷新qss
/*extern 关键字起到了**声明（Declaration）而非定义（Definition）**的作用。
简单来说，它的核心作用是：告诉编译器这个变量在其他地方已经定义过了，现在只是在这里“打个招呼”，以便当前文件可以使用它。*/
extern std::function<void(QWidget*)> repolish;
#endif // GLOBAL_H
