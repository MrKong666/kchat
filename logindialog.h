#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
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
signals:
    void switchRegister();
};

#endif // LOGINDIALOG_H
