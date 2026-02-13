#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"logindialog.h"
#include"registerdialog.h"
#include"resetdialog.h"
/**
 * @file mainwindow.h
 * @brief  主窗口
 *
 * @date  2025/12/30
 * @author 孔祥锐
 */


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(Ui::MainWindow *ui, LoginDialog *login_dlg, RegisterDialog *reg_dlg);
    ~MainWindow();
public slots:
    void SlotSwitchReg();
    void SlotSwitchLogin();
    void SlotSwitchLogin2();
    void SlotSwitchReset();
private:
    Ui::MainWindow *ui;
    LoginDialog* _login_dlg;
    RegisterDialog* _reg_dlg;
    ResetDialog* _reset_dlg;
};
#endif // MAINWINDOW_H
