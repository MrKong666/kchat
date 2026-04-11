#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"global.h"
/**
 * @file logindialog.h
 * @brief  注册窗口
 *
 * @date  2025/12/31
 * @author 孔祥锐
 */

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    void initHttpHandlers();
    void initHead();
    bool checkUserValid();
    bool checkPwdValid();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    QMap<TipErr,QString>_tip_errs;
    void showTip(QString str,bool b_ok);
    bool enableBtn(bool enabled);
    QMap<ReqId,std::function<void(const QJsonObject)>>_handlers;
    int _uid;
    QString _token;
signals:
    void switchRegister();
    void switchReset();
    void sig_connect_tcp(ServerInfo si);
public slots:
    void slot_forget_pwd();
    void slot_login_mod_finish(ReqId id,QString res,ErrorCodes err);
private slots:
    void on_login_btn_clicked();
    void slot_tcp_con_finish(bool bsuccess);
    void slot_login_failed(int);
};

#endif // LOGINDIALOG_H
