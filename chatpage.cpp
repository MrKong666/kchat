#include "chatpage.h"
#include "ui_chatpage.h"
#include <QStyleOption>
#include <QPainter>
#include "ChatItemBase.h"
#include "TextBubble.h"
#include "PictureBubble.h"


/**
 * 构造函数：初始化界面与按钮状态
 */
ChatPage::ChatPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage)
{
    ui->setupUi(this);

    // 设置发送和接收按钮的三态样式（普通、悬停、按下）
    ui->send_btn->SetState("normal","hover","press");
    ui->send_btn->SetState("normal","hover","press");


    ui->receive_btn->SetState("normal","hover","press");
    ui->receive_btn->SetState("normal","hover","press");

    // 设置表情和文件图标的三态样式
    ui->emo_lb->SetState("normal","hover","press","normal","hover","press");
    ui->file_lb->SetState("normal","hover","press","normal","hover","press");
}

ChatPage::~ChatPage()
{
    delete ui;
}

/**
 * 绘图事件：为了支持在 QSS 中给自定义窗口设置 background-image 或 border 等样式，
 * 必须重写 paintEvent 并使用 QStyleOption 初始化。
 */
void ChatPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    // 确保样式表在继承自 QWidget 的类上生效
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChatPage::on_receive_btn_clicked()
{

}

/**
 * 核心逻辑：点击“发送”按钮的处理函数
 * 作用：从输入框获取解析后的消息列表，逐一创建对应的气泡并显示到列表控件中
 */
void ChatPage::on_send_btn_clicked()
{
    auto pTextEdit = ui->chatEdit; // 获取自定义的文字编辑器对象
    ChatRole role = ChatRole::Self; // 标记身份为“自己”
    QString userName = QStringLiteral("kxr"); // 模拟当前用户名
    QString userIcon = ":/res/head_1.jpg";       // 模拟当前用户头像

    // 1. 调用输入框的 getMsgList 方法，获取解析好的消息结构体列表（含文字、图片等）
    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();

    // 2. 遍历消息列表，将每一条信息转化为 UI 上的聊天气泡
    for(int i=0; i<msgList.size(); ++i)
    {
        QString type = msgList[i].msgFlag; // 获取消息类型（text, image, file）

        // 创建聊天条目基类（负责显示头像、名字和布局容器）
        ChatItemBase *pChatItem = new ChatItemBase(role);
        pChatItem->setUserName(userName);
        pChatItem->setUserIcon(QPixmap(userIcon));

        QWidget *pBubble = nullptr; // 气泡插件指针

        // 3. 根据类型创建具体的气泡组件
        if(type == "text")
        {
            // 创建文本气泡
            pBubble = new TextBubble(role, msgList[i].content);
        }
        else if(type == "image")
        {
            // 创建图片气泡，msgList[i].content 存储的是图片的路径
            pBubble = new PictureBubble(QPixmap(msgList[i].content), role);
        }
        else if(type == "file")
        {
            // TODO: 处理文件类型的气泡（目前为空）
        }

        // 4. 如果气泡创建成功，将其装载到 ChatItem 中并添加到滚动列表
        if(pBubble != nullptr)
        {
            pChatItem->setWidget(pBubble); // 将气泡放入条目容器
            ui->chat_data_list->appendChatItem(pChatItem); // 将完整条目添加到聊天记录展示区
        }
    }
}
