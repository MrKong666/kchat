#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg=new LoginDialog(this);
    setCentralWidget(_login_dlg);
    // _login_dlg->show();

    //创建注册消息连接切换注册窗口
    connect(_login_dlg,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);
    _reg_dlg=new RegisterDialog(this);
    //设置窗口嵌入
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

}

MainWindow::~MainWindow()
{
    delete ui;
    /*这里直接回收会存在内存泄漏问题
        给两个窗口设置父窗口利用qt对象树机制回收*/
    // if(_login_dlg){
    //     delete _login_dlg;
    //     _login_dlg=nullptr;
    // }
    // if(_reg_dlg){
    //     delete _reg_dlg;
    //     _reg_dlg=nullptr;
    // }
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}
