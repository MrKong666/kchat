#ifndef HTTPMGR_H
#define HTTPMGR_H
/**
 * @file httpmgr.h
 * @brief  http管理类
 *
 * @date  2026/01/21
 * @author 孔祥锐
 */

#include"singleton.h"
#include<QString>
#include<QUrl>
#include<QObject>
#include<QNetworkAccessManager>
#include<QJsonObject>
#include<QJsonDocument>
/*
 * CRTP 的全称是 Curiously Recurring Template Pattern（奇异递归模板模式）。
 * 它是 C++ 中一种非常强大且常用的设计模式，核心思想是：子类继承自一个将子类本身作为模板参数的基类。
 * 之所以称之为“递归”，是因为在定义 Derived 的过程中引用了 Derived 本身。虽然看起来像无限循环，
 * 但由于 C++ 模板是延迟实例化的，编译器在处理 Base<Derived> 时只需要知道 Derived 是个名字，
 * 直到调用具体成员函数时才会去解析 Derived 的内容。CRTP 的核心作用：静态多态 (Static Polymorphism)
这是 CRTP 最常见的用途。在传统的虚函数（动态多态）中，程序在运行时通过虚函数表（vtable）查找要调用的函数，
这会有轻微的性能开销。
而在 CRTP 中，多态是在编译期完成的，没有虚函数表的开销，这被称为“静态多态”。*/
/*QObject: 必须继承它才能使用 Qt 的核心特性（信号槽 signals/slots、Q_OBJECT 宏等）。
Singleton<HttpMgr>: 实现单例模式，确保整个程序只有一个网络管理者。
std::enable_shared_from_this<HttpMgr>: 这是该代码的一个高阶技巧，解决了在异步回调（Lambda 表达式）中安全访问 this 的问题。*/
class HttpMgr:public QObject,public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url,QJsonObject json,ReqId req_id,Modules mod);
private:
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager _manager;

private slots:
    void slot_http_finish(ReqId id,QString res,ErrorCodes err,Modules mod);
signals:
    void sig_http_finish(ReqId id,QString res,ErrorCodes err,Modules mod  );
    void sig_reg_mod_finish(ReqId id,QString res,ErrorCodes err);
     void sig_reset_mod_finish(ReqId id,QString res,ErrorCodes err);

};

#endif // HTTPMGR_H
