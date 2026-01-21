#include "httpmgr.h"

HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr() {

    connect(this,&HttpMgr::sig_http_finish,this,&HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data=QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self =shared_from_this();
    /*网络请求是异步的。如果请求还没结束，HttpMgr 对象却被销毁了，Lambda 闭包内如果捕获的是 this 指针，就会发生崩溃。
原理：shared_from_this() 会返回一个指向当前对象的 shared_ptr。通过将 self 捕获进 Lambda，会增加 HttpMgr 的引用计数。
这保证了只要网络请求还没处理完，HttpMgr 对象就一定不会被析构。*/
    QNetworkReply*reply=_manager.post(request,data);
    QObject::connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){
        //处理错误情况
        if(reply->error()!=QNetworkReply::NoError){
            qDebug()<<reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
            reply->deleteLater();
            return;
        }
        //无错误
        QString res=reply->readAll();
        //发送信号通知完成
        emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
        /*在 Qt 中，直接 delete reply 是危险的，因为此时 QNetworkReply 可能仍在处理某些信号。
         *  deleteLater() 会将对象放入事件队列，待当前事件处理完毕后再安全删除，有效防止悬空指针错误。*/
        return;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod==Modules::REGISTERMOD){
        //发送信号通知指定模块http的响应结束了
        emit sig_reg_mod_finish(id,res,err);
    }
}
