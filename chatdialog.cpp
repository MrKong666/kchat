#include "chatdialog.h"
#include "ui_chatdialog.h"
#include<QAction>
#include<QRandomGenerator>
#include"chatuserlist.h"
#include"chatuserwid.h"
#include"logindialog.h"
#include"loadingdlg.h"
#include<QMouseEvent>
#include"usermgr.h"
#include"tcpmgr.h"
ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog),_mode(ChatUIMode::ChatMode),
    _state(ChatUIMode::ChatMode),_b_loading(false)
{
    ui->setupUi(this);
    ui->add_btn->SetState("normal","hover","press");
    ui->search_edit->SetMaxLength(15);

    //搜索动作
    QAction*searchAction=new QAction(ui->search_edit);
    searchAction->setIcon(QIcon(":/res/search.png"));
    ui->search_edit->addAction(searchAction,QLineEdit::LeadingPosition);
    ui->search_edit->setPlaceholderText(QStringLiteral("搜索"));

    //清除动作设置图标
    QAction*clearAction=new QAction(ui->search_edit);
    clearAction->setIcon(QIcon(":/res/close_transparent.png"));

    //动作放到lineedit上面
    ui->search_edit->addAction(clearAction,QLineEdit::TrailingPosition);

    //有文字时变成清除图标
    connect(ui->search_edit,&QLineEdit::textChanged,[clearAction](const QString&text){
        if(!text.isEmpty()){
            clearAction->setIcon(QIcon(":/res/close_search.png"));
        }
        else{
            clearAction->setIcon(QIcon(":/res/close_transparent.png"));
        }
    });

    //点清除时清除文本
    connect(clearAction,&QAction::triggered,[this,clearAction](){
        ui->search_edit->clear();
        clearAction->setIcon(QIcon(":/res/close_transparent.png"));
        ui->search_edit->clearFocus();

        ShowSearch(false);
    });
    ShowSearch(false);

    connect(ui->chat_user_list,
            &ChatUserList::sig_loading_chat_user,this,&ChatDialog::slot_loading_chat_user);
    addChatUserList();

    QPixmap pixmap(":/res/head_1.jpg"); // 加载图片
    ui->side_head_lb->setPixmap(pixmap); // 将图片设置到QLabel上
    QPixmap scaledPixmap = pixmap.scaled( ui->side_head_lb->size(), Qt::KeepAspectRatio); // 将图片缩放到label的大小
    ui->side_head_lb->setPixmap(scaledPixmap); // 将缩放后的图片设置到QLabel上
    ui->side_head_lb->setScaledContents(true); // 设置QLabel自动缩放图片内容以适应大小


    ui->side_chat_lb->setProperty("state","normal");

    ui->side_chat_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    ui->side_contact_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");


    AddLBGroup(ui->side_chat_lb);
    AddLBGroup(ui->side_contact_lb);

    connect(ui->side_chat_lb, &StateWidget::clicked, this, &ChatDialog::slot_side_chat);
    connect(ui->side_contact_lb, &StateWidget::clicked, this, &ChatDialog::slot_side_contact);

    //链接搜索框输入变化
    connect(ui->search_edit, &QLineEdit::textChanged, this, &ChatDialog::slot_text_changed);

    ShowSearch(false);
    //检测鼠标点击位置判断是否要清空搜索框
        this->installEventFilter(this); // 安装事件过滤器
    //设置聊天label选中状态
    ui->side_chat_lb->SetSelected(true);


    //为searchlist 设置search edit
    ui->search_list->SetSearchEdit(ui->search_edit);

    //连接申请添加好友信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_friend_apply, this, &ChatDialog::slot_apply_friend);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::addChatUserList()
{
    //创建QListwidgetItem,并设置自定义widget
    for(int i=0;i<13;i++){
        int randomValue=QRandomGenerator::global()->bounded(100);
        int str_i=randomValue%strs.size();
        int head_i=randomValue%heads.size();
        int name_i=randomValue%names.size();

        auto*chat_user_wid=new ChatUserWid();
        chat_user_wid->SetInfo(names[name_i],/*QString(":/")+*/heads[head_i],strs[str_i]);
        QListWidgetItem*item=new QListWidgetItem;
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chat_user_list->addItem(item);
        ui->chat_user_list->setItemWidget(item,chat_user_wid);
    }
}

void ChatDialog::ClearLabelState(StateWidget *lb)
{
    for(auto & ele: _lb_list){
        if(ele == lb){
            continue;
        }

        ele->ClearState();
    }
}

bool ChatDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        handleGlobalMousePress(mouseEvent);
    }
    return QDialog::eventFilter(watched, event);
}

void ChatDialog::handleGlobalMousePress(QMouseEvent *event)
{
    // 实现点击位置的判断和处理逻辑
    // 先判断是否处于搜索模式，如果不处于搜索模式则直接返回
    if( _mode != ChatUIMode::SearchMode){
        qDebug()<<_mode;
        return;
    }

    // 将鼠标点击位置转换为搜索列表坐标系中的位置
    // 1. 使用 globalPosition() 获取浮点坐标
    // 2. mapFromGlobal 现在也支持接收 QPointF
    QPointF posInSearchList = ui->search_list->mapFromGlobal(event->globalPosition());
    qDebug()<<"111111";
    // 3. contains 函数可以自动处理 QPointF 与 QRect 的匹配
    // 判断点击位置是否在搜索列表的范围内
    if (!ui->search_list->rect().contains(posInSearchList.toPoint())) {
        // 如果不在搜索列表内，清空输入框并隐藏搜索结果
        ui->search_edit->clear();
        ShowSearch(false);
    }
}

void ChatDialog::ShowSearch(bool bsearch)
{
    if(bsearch){
        ui->chat_user_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode=ChatUIMode::SearchMode;
    }
    else if(_state==ChatUIMode::ChatMode){
        ui->chat_user_list->show();
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode=ChatUIMode::ChatMode;
    }
    else if(_state==ChatUIMode::ContactMode){
        ui->chat_user_list->hide();
        ui->con_user_list->show();
        ui->search_list->hide();
        _mode=ChatUIMode::ContactMode;
    }
}

void ChatDialog::AddLBGroup(StateWidget *lb)
{
    _lb_list.push_back(lb);
}

void ChatDialog::slot_loading_chat_user()
{
    if(_b_loading)return;

    _b_loading=true;

    LoadingDlg*loadingDialog=new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    qDebug()<<"add new data to list.......";
    addChatUserList();

    loadingDialog->deleteLater();

    _b_loading=false;


}

void ChatDialog::slot_side_chat()
{
    qDebug()<< "receive side chat clicked";
    ClearLabelState(ui->side_chat_lb);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    _state = ChatUIMode::ChatMode;
    ShowSearch(false);
}

void ChatDialog::slot_side_contact(){
    qDebug()<< "receive side contact clicked";
    ClearLabelState(ui->side_contact_lb);
    //设置
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
    _state = ChatUIMode::ContactMode;
    ShowSearch(false);
}
void ChatDialog::slot_text_changed(const QString &str)
{
    //qDebug()<< "receive slot text changed str is " << str;
    if (!str.isEmpty()) {
        ShowSearch(true);
    }
}

void ChatDialog::slot_apply_friend(std::shared_ptr<AddFriendApply> apply)
{
    qDebug() << "receive apply friend slot, applyuid is " << apply->_from_uid << " name is "
             << apply->_name << " desc is " << apply->_desc;

    bool b_already = UserMgr::GetInstance()->AlreadyApply(apply->_from_uid);
    if(b_already){
        return;
    }

    UserMgr::GetInstance()->AddApplyList(std::make_shared<ApplyInfo>(apply));
    ui->side_contact_lb->ShowRedPoint(true);
    ui->con_user_list->ShowRedPoint(true);
    ui->friend_apply_page->AddNewApply(apply);
}
