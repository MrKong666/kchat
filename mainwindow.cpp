#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"tcpmgr.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg=new LoginDialog(this);
    //设置窗口嵌入
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);
    // _login_dlg->show();

    //创建注册消息连接切换注册窗口
    connect(_login_dlg,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);


    //连接登录界面和忘记密码界面
    connect(_login_dlg,&LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);
//连接创建聊天界面信号
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_swich_chatdlg,this,
            &MainWindow::SlotSwitchChat);
         // emit TcpMgr::GetInstance()->sig_swich_chatdlg();
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
    _reg_dlg=new RegisterDialog(this);
    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(_reg_dlg,&RegisterDialog::sigSwitchLogin,this,&MainWindow::SlotSwitchLogin);
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}

void MainWindow::SlotSwitchLogin()
{
    _login_dlg=new LoginDialog(this);
    setCentralWidget(_login_dlg);
    // _login_dlg->show();
    //设置窗口嵌入
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    _reg_dlg->hide();
    _login_dlg->show();
    //创建注册消息连接切换注册窗口
    connect(_login_dlg,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);
     connect(_login_dlg,&LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);


}

void MainWindow::SlotSwitchLogin2()
{
    _login_dlg=new LoginDialog(this);
    setCentralWidget(_login_dlg);
    // _login_dlg->show();
    //设置窗口嵌入
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    _reset_dlg->hide();
    _login_dlg->show();
    //创建注册消息连接切换注册窗口
    connect(_login_dlg,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);
    connect(_login_dlg,&LoginDialog::switchReset,this,&MainWindow::SlotSwitchReset);


}



void MainWindow::SlotSwitchReset()
{
    //创建一个reset窗口，设置为中心窗口
    _reset_dlg=new ResetDialog(this);
    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_reset_dlg);

    _login_dlg->hide();
    _reset_dlg->show();
    //注册返回登录信号和槽函数
    connect(_reset_dlg,&ResetDialog::switchLogin,this,&MainWindow::SlotSwitchLogin2);
}

void MainWindow::SlotSwitchChat()
{
    _chat_dlg=new ChatDialog();
    _chat_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_chat_dlg);
    _chat_dlg->show();
    this->setMinimumSize(QSize(1050,900));
    this->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
}
