#include "applyfriend.h"
#include "ui_applyfriend.h"
#include "clickedlabel.h"
#include "friendlabel.h"
#include <QScrollBar>
#include "usermgr.h"
#include "tcpmgr.h"
#include <QJsonDocument>

/**
 * @brief 构造函数：初始化添加好友界面
 */
ApplyFriend::ApplyFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ApplyFriend),
    _label_point(2,6) // _label_point 用于记录上方“已选标签”区域下一个标签该插入的初始(x,y)坐标
{
    ui->setupUi(this);
    // 隐藏对话框原生的标题栏，方便实现无边框自定义UI
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("ApplyFriend");
    this->setModal(true); // 设置为模态对话框（必须处理完这个弹窗才能点击主界面）

    // 设置各个输入框的占位符（默认提示文字）
    ui->name_ed->setPlaceholderText(tr("shy"));
    ui->lb_ed->setPlaceholderText("搜索、添加标签");
    ui->back_ed->setPlaceholderText("kxr"); // 备注名

    // 初始化标签输入框的属性和初始位置
    ui->lb_ed->SetMaxLength(21);
    ui->lb_ed->move(2, 2);
    ui->lb_ed->setFixedHeight(20);
    ui->lb_ed->setMaxLength(10);
    ui->input_tip_wid->hide(); // 隐藏自动补全/添加提示悬浮窗

    _tip_cur_point = QPoint(5, 5); // 下方“备选标签库”排版的初始坐标

    // 预设的一批推荐标签
    _tip_data = { "同学","家人","菜鸟教程","C++ Primer","Rust 程序设计",
                 "父与子学Python","nodejs开发指南","go 语言开发指南",
                 "游戏伙伴","金融投资","微信读书","拼多多拼友" };

    // 点击“展示更多”标签时的信号槽
    connect(ui->more_lb, &ClickedOnceLabel::clicked, this, &ApplyFriend::ShowMoreLabel);

    InitTipLbs(); // 渲染初始的备选标签（默认只显示前两行）

    // 连接标签输入框的交互事件（回车、文本变化、失去焦点）
    connect(ui->lb_ed, &CustomizeEdit::returnPressed, this, &ApplyFriend::SlotLabelEnter);
    connect(ui->lb_ed, &CustomizeEdit::textChanged, this, &ApplyFriend::SlotLabelTextChange);
    connect(ui->lb_ed, &CustomizeEdit::editingFinished, this, &ApplyFriend::SlotLabelEditFinished);

    // 点击自动补全提示时，添加标签
    connect(ui->tip_lb, &ClickedOnceLabel::clicked, this, &ApplyFriend::SlotAddFirendLabelByClickTip);

    // 默认隐藏滚动条（使得界面更清爽），通过事件过滤器在鼠标悬停时才显示
    ui->scrollArea->horizontalScrollBar()->setHidden(true);
    ui->scrollArea->verticalScrollBar()->setHidden(true);
    ui->scrollArea->installEventFilter(this);

    // 设置确定和取消按钮的三态样式（通过QSS或者绘图控制）
    ui->sure_btn->SetState("normal","hover","press");
    ui->cancel_btn->SetState("normal","hover","press");

    // 连接确认和取消按钮的槽函数
    connect(ui->cancel_btn, &QPushButton::clicked, this, &ApplyFriend::SlotApplyCancel);
    connect(ui->sure_btn, &QPushButton::clicked, this, &ApplyFriend::SlotApplySure);
}

ApplyFriend::~ApplyFriend()
{
    qDebug()<< "ApplyFriend destruct";
    delete ui;
}

/**
 * @brief 初始化下方备选标签库（流式布局算法）
 * 逻辑：动态计算文字宽度，如果当前行放不下了，就换行。默认最多显示两行。
 */
void ApplyFriend::InitTipLbs()
{
    int lines = 1; // 记录当前行数
    for(int i = 0; i < _tip_data.size(); i++){

        auto* lb = new ClickedLabel(ui->lb_list);
        lb->SetState("normal", "hover", "pressed", "selected_normal",
                     "selected_hover", "selected_pressed");
        lb->setObjectName("tipslb");
        lb->setText(_tip_data[i]);
        // 绑定点击备选标签的事件：选中它并添加到上方
        connect(lb, &ClickedLabel::clicked, this, &ApplyFriend::SlotChangeFriendLabelByTip);

        // Qt 6 标准：使用 horizontalAdvance 获取精确的文本宽度
        QFontMetrics fontMetrics(lb->font());
        auto textWidth = fontMetrics.horizontalAdvance(lb->text());
        int textHeight = fontMetrics.height();

        // 流式布局核心：判断当前X坐标 + 文字宽度 + 间距 是否超过了容器总宽度
        if (_tip_cur_point.x() + textWidth + tip_offset > ui->lb_list->width()) {
            lines++;
            if (lines > 2) {
                // 如果超过两行，剩余的标签先不生成（等点击“展示更多”再处理）
                delete lb;
                return;
            }
            // 换行：X归位，Y增加一行的高度
            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);
        }

        auto next_point = _tip_cur_point;
        // 放置标签，并计算出下一个标签的起始X坐标
        AddTipLbs(lb, _tip_cur_point, next_point, textWidth, textHeight);
        _tip_cur_point = next_point; // 更新坐标游标
    }
}

/**
 * @brief 将创建好的备选标签移动到指定位置，并记录到管理容器中
 */
void ApplyFriend::AddTipLbs(ClickedLabel* lb, QPoint cur_point, QPoint& next_point, int text_width, int text_height)
{
    lb->move(cur_point);
    lb->show();
    _add_labels.insert(lb->text(), lb);       // 存入 Map 方便后续通过文字查找标签对象
    _add_label_keys.push_back(lb->text());    // 存入 List 保证顺序

    // 计算当前行下一个标签的起始 X 坐标 (当前X + 文字宽度 + 50像素的固定间距)
    next_point.setX(lb->pos().x() + text_width + 15);
    next_point.setY(lb->pos().y());
}

/**
 * @brief 事件过滤器：处理滚动区域的鼠标悬停效果
 */
bool ApplyFriend::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->scrollArea && event->type() == QEvent::Enter) {
        ui->scrollArea->verticalScrollBar()->setHidden(false); // 鼠标进入显示滚动条
    } else if (obj == ui->scrollArea && event->type() == QEvent::Leave) {
        ui->scrollArea->verticalScrollBar()->setHidden(true);  // 鼠标离开隐藏滚动条
    }
    return QObject::eventFilter(obj, event);
}

/**
 * @brief 设置搜索到的目标用户信息
 */
void ApplyFriend::SetSearchInfo(std::shared_ptr<SearchInfo> si)
{
    _si = si;
    auto applyname = UserMgr::GetInstance()->GetName(); // 我方称呼（我是谁）
    auto bakname = si->_name;                           // 对方昵称（默认填入备注栏）
    ui->name_ed->setText(applyname);
    ui->back_ed->setText(bakname);
}

/**
 * @brief 展开完整的备选标签库
 * 逻辑：重置容器宽度，重新计算所有已有标签的坐标，然后把没显示的标签全部生成出来
 */
void ApplyFriend::ShowMoreLabel()
{
    qDebug()<< "receive more label clicked";
    ui->more_lb_wid->hide(); // 隐藏“展示更多”按钮

    ui->lb_list->setFixedWidth(325); // 展开后的容器宽度
    _tip_cur_point = QPoint(5, 5);
    auto next_point = _tip_cur_point;
    int textWidth;
    int textHeight;

    // 1. 重新排列已经生成的标签（因为宽度变了，之前的换行位置可能不适用了）
    for(auto & added_key : _add_label_keys){
        auto added_lb = _add_labels[added_key];

        QFontMetrics fontMetrics(added_lb->font());
        textWidth = fontMetrics.horizontalAdvance(added_lb->text());
        textHeight = fontMetrics.height();

        if(_tip_cur_point.x() + textWidth + tip_offset > ui->lb_list->width()){
            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);
        }
        added_lb->move(_tip_cur_point);

        next_point.setX(added_lb->pos().x() + textWidth + 15); // 展开后间距改为 15
        next_point.setY(_tip_cur_point.y());
        _tip_cur_point = next_point;
    }

    // 2. 生成并排列之前被隐藏的剩余标签
    for(int i = 0; i < _tip_data.size(); i++){
        auto iter = _add_labels.find(_tip_data[i]);
        if(iter != _add_labels.end()){
            continue; // 如果已经生成过了，跳过
        }

        auto* lb = new ClickedLabel(ui->lb_list);
        lb->SetState("normal", "hover", "pressed", "selected_normal", "selected_hover", "selected_pressed");
        lb->setObjectName("tipslb");
        lb->setText(_tip_data[i]);
        connect(lb, &ClickedLabel::clicked, this, &ApplyFriend::SlotChangeFriendLabelByTip);

        QFontMetrics fontMetrics(lb->font());
        auto textWidth = fontMetrics.horizontalAdvance(lb->text());
        int textHeight = fontMetrics.height();

        if (_tip_cur_point.x() + textWidth + tip_offset > ui->lb_list->width()) {
            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);
        }

        next_point = _tip_cur_point;
        AddTipLbs(lb, _tip_cur_point, next_point, textWidth, textHeight);
        _tip_cur_point = next_point;
    }

    // 重新计算并调整父容器的高度，确保不会被截断，并让滚动条生效
    int diff_height = next_point.y() + textHeight + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + textHeight + tip_offset);
    ui->scrollcontent->setFixedHeight(ui->scrollcontent->height() + diff_height);
}

/**
 * @brief 重新排版上方“已选定标签”区域
 * 触发时机：当用户删除了某个已选标签时，为了填补空白，需要把后面的标签往前挪
 */
void ApplyFriend::resetLabels()
{
    auto max_width = ui->gridWidget->width();
    auto label_height = 0;

    // 遍历所有已选标签重新计算坐标
    for(auto iter = _friend_labels.begin(); iter != _friend_labels.end(); iter++){
        // 如果当前行放不下该标签，则换行
        if( _label_point.x() + iter.value()->width() > max_width) {
            _label_point.setY(_label_point.y() + iter.value()->height() + 6);
            _label_point.setX(2);
        }

        iter.value()->move(_label_point);
        iter.value()->show();

        // 推进下一个坐标点
        _label_point.setX(_label_point.x() + iter.value()->width() + 2);
        _label_point.setY(_label_point.y());
        label_height = iter.value()->height();
    }

    // 调整文本输入框(lb_ed)的位置，让它紧跟在最后一个标签的后面
    if(_friend_labels.isEmpty()){
        ui->lb_ed->move(_label_point);
        return;
    }

    if(_label_point.x() + MIN_APPLY_LABEL_ED_LEN > ui->gridWidget->width()){
        // 如果剩下的空间不够放输入框了，把输入框换到下一行
        ui->lb_ed->move(2, _label_point.y() + label_height + 6);
    }else{
        ui->lb_ed->move(_label_point);
    }
}

/**
 * @brief 添加一个新的标签到上方“已选区域”
 */
void ApplyFriend::addLabel(QString name)
{
    // 如果已经存在该标签，清空输入框并返回，防止重复添加
    if (_friend_labels.find(name) != _friend_labels.end()) {
        ui->lb_ed->clear();
        return;
    }

    // 创建上方特有的 FriendLabel（带有小叉叉可以关闭的样式）
    auto tmplabel = new FriendLabel(ui->gridWidget);
    tmplabel->SetText(name);
    tmplabel->setObjectName("FriendLabel");

    auto max_width = ui->gridWidget->width();

    // 换行判定
    if (_label_point.x() + tmplabel->width() > max_width) {
        _label_point.setY(_label_point.y() + tmplabel->height() + 6);
        _label_point.setX(2);
    }

    tmplabel->move(_label_point);
    tmplabel->show();

    // 记录到数据结构中
    _friend_labels[tmplabel->Text()] = tmplabel;
    _friend_label_keys.push_back(tmplabel->Text());

    // 绑定删除按钮的信号，点击叉叉触发 SlotRemoveFriendLabel
    connect(tmplabel, &FriendLabel::sig_close, this, &ApplyFriend::SlotRemoveFriendLabel);

    // 推进 X 坐标并调整输入框位置
    _label_point.setX(_label_point.x() + tmplabel->width() + 2);
    if (_label_point.x() + MIN_APPLY_LABEL_ED_LEN > ui->gridWidget->width()) {
        ui->lb_ed->move(2, _label_point.y() + tmplabel->height() + 2);
    } else {
        ui->lb_ed->move(_label_point);
    }

    ui->lb_ed->clear(); // 清空输入框

    // 动态撑开父容器高度
    if (ui->gridWidget->height() < _label_point.y() + tmplabel->height() + 2) {
        ui->gridWidget->setFixedHeight(_label_point.y() + tmplabel->height() * 2 + 2);
    }
}

/**
 * @brief 槽函数：在输入框中按下回车时触发
 */
void ApplyFriend::SlotLabelEnter()
{
    if(ui->lb_ed->text().isEmpty()){ return; }

    auto text = ui->lb_ed->text();
    addLabel(text); // 添加到上方已选区
    ui->input_tip_wid->hide(); // 隐藏悬浮提示

    // 判断该输入的标签是否是一个全新的标签，如果是则加入预设数据列表中
    auto find_it = std::find(_tip_data.begin(), _tip_data.end(), text);
    if (find_it == _tip_data.end()) {
        qDebug()<<"111111";
        _tip_data.push_back(text);
    }

    // 检查下方备选区是否已经渲染过这个标签
    auto find_add = _add_labels.find(text);
    if (find_add != _add_labels.end()) {
        find_add.value()->SetCurState(ClickLbState::Selected); // 设置为高亮选中状态
        return;
    }

    // 如果备选区还没这个标签（用户自定义的新标签），在下方追加一个
    auto* lb = new ClickedLabel(ui->lb_list);
    lb->SetState("normal", "hover", "pressed", "selected_normal", "selected_hover", "selected_pressed");
    lb->setObjectName("tipslb");
    lb->setText(text);
    connect(lb, &ClickedLabel::clicked, this, &ApplyFriend::SlotChangeFriendLabelByTip);

    QFontMetrics fontMetrics(lb->font());
    auto textWidth = fontMetrics.horizontalAdvance(lb->text());
    int textHeight = fontMetrics.height();

    if (_tip_cur_point.x() + textWidth + tip_offset + 3 > ui->lb_list->width()) {
        _tip_cur_point.setX(5);
        _tip_cur_point.setY(_tip_cur_point.y() + textHeight + 15);
    }

    auto next_point = _tip_cur_point;
    AddTipLbs(lb, _tip_cur_point, next_point, textWidth, textHeight);
    _tip_cur_point = next_point;

    // 调整容器高度并设为选中状态
    int diff_height = next_point.y() + textHeight + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + textHeight + tip_offset);
    lb->SetCurState(ClickLbState::Selected);
    ui->scrollcontent->setFixedHeight(ui->scrollcontent->height() + diff_height);
}

/**
 * @brief 槽函数：删除已选中的标签
 */
void ApplyFriend::SlotRemoveFriendLabel(QString name)
{
    qDebug() << "receive close signal";

    // 坐标重置到起点准备重新排版
    _label_point.setX(2);
    _label_point.setY(6);

    auto find_iter = _friend_labels.find(name);
    if(find_iter == _friend_labels.end()){ return; }

    // 从 keys 列表中剔除
    auto find_key = _friend_label_keys.end();
    for(auto iter = _friend_label_keys.begin(); iter != _friend_label_keys.end(); iter++){
        if(*iter == name){
            find_key = iter;
            break;
        }
    }
    if(find_key != _friend_label_keys.end()){
        _friend_label_keys.erase(find_key);
    }

    delete find_iter.value(); // 删除UI控件
    _friend_labels.erase(find_iter); // 移除数据记录

    resetLabels(); // 重新排版剩下的标签

    // 同步取消下方备选区对应标签的“高亮选中”状态
    auto find_add = _add_labels.find(name);
    if(find_add == _add_labels.end()){ return; }
    find_add.value()->ResetNormalState();
}

/**
 * @brief 槽函数：点击下方备选标签时，同步上方区域
 */
void ApplyFriend::SlotChangeFriendLabelByTip(QString lbtext, ClickLbState state)
{qDebug() << "点击了标签:" << lbtext << " 当前状态:" << state;
    auto find_iter = _add_labels.find(lbtext);
    if(find_iter == _add_labels.end()){ return; }

    if(state == ClickLbState::Selected){
        addLabel(lbtext); // 选中了，添加上去
        return;
    }

    if(state == ClickLbState::Normal){
        SlotRemoveFriendLabel(lbtext); // 取消选中，删掉它
        return;
    }
}

/**
 * @brief 槽函数：输入框文字变化时，弹出“添加...”悬浮提示窗
 */
void ApplyFriend::SlotLabelTextChange(const QString& text)
{
    if (text.isEmpty()) {
        ui->tip_lb->setText("");
        ui->input_tip_wid->hide();
        return;
    }

    auto iter = std::find(_tip_data.begin(), _tip_data.end(), text);
    if (iter == _tip_data.end()) {
        // 如果是个新词，提示例如 “添加标签: text” (假设 add_prefix="添加标签:")
        auto new_text = add_prefix + text;
        ui->tip_lb->setText(new_text);
        ui->input_tip_wid->show();
        return;
    }
    ui->tip_lb->setText(text);
    ui->input_tip_wid->show();
}

/**
 * @brief 槽函数：输入完毕失去焦点时隐藏提示窗
 */
void ApplyFriend::SlotLabelEditFinished()
{
    ui->input_tip_wid->hide();
}

/**
 * @brief 槽函数：点击悬浮提示窗时，把内容加成标签
 */
void ApplyFriend::SlotAddFirendLabelByClickTip(QString text)
{
    // 剥除前面的 "添加标签:" 前缀，提取纯净文字
    int index = text.indexOf(add_prefix);
    if (index != -1) {
        text = text.mid(index + add_prefix.length());
    }

    // 接下来的逻辑等价于按下回车键（SlotLabelEnter）
    addLabel(text);
    /* ... 后面与 SlotLabelEnter 的新建下方标签逻辑完全一致 ... */
}

/**
 * @brief 槽函数：点击“确定”按钮触发，向服务器发送加好友请求
 */
void ApplyFriend::SlotApplySure()
{
    qDebug()<<"Slot Apply Sure called" ;

    QJsonObject jsonObj;
    auto uid = UserMgr::GetInstance()->GetUid(); // 自己的用户ID
    jsonObj["uid"] = uid;
    qDebug()<<"自己的id是："<<uid;
    // 获取自己填写的打招呼内容
    auto name = ui->name_ed->text();
    if(name.isEmpty()){
        name = ui->name_ed->placeholderText();
    }
    jsonObj["applyname"] = name;

    // 获取给对方打的备注
    auto bakname = ui->back_ed->text();
    if(bakname.isEmpty()){
        bakname = ui->back_ed->placeholderText();
    }
    jsonObj["bakname"] = bakname;
    jsonObj["touid"] = _si->_uid; // 目标用户的ID

    QJsonDocument doc(jsonObj);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact); // 序列化为JSON字符串
    qDebug()<<"2222222222";
    // 将协议号（ReqId::ID_ADD_FRIEND_REQ）和数据通过 TCP 单例发送给 Chat Server
    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_ADD_FRIEND_REQ, jsonData);

    this->hide();
    deleteLater(); // 销毁当前弹窗释放内存
}

/**
 * @brief 槽函数：点击“取消”按钮触发
 */
void ApplyFriend::SlotApplyCancel()
{
    qDebug() << "Slot Apply Cancel";
    this->hide();
    deleteLater();
}



