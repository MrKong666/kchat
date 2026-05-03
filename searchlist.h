#ifndef SEARCHLIST_H
#define SEARCHLIST_H

#include <QListWidget>
#include <QWheelEvent>
#include <QEvent>
#include <QScrollBar>
#include <QDebug>
#include <QDialog>
#include <memory>
#include "userdata.h"
#include "loadingdlg.h"

/**
 * SearchList 类：自定义搜索结果列表
 * 功能：展示搜索到的用户信息，处理点击事件，并优化了滚动条的显示体验
 */
class SearchList: public QListWidget
{
    Q_OBJECT
public:
    SearchList(QWidget *parent = nullptr);

    void CloseFindDlg();             // 关闭搜索相关的对话框（如查找好友弹窗）
    void SetSearchEdit(QWidget* edit); // 绑定搜索输入框，以便进行联动操作

protected:
    /**
     * 事件过滤器：实现更细腻的交互
     * 1. 鼠标悬停在列表上时才显示滚动条，离开则隐藏
     * 2. 自定义滚轮滚动幅度
     */
    bool eventFilter(QObject *watched, QEvent *event) override {
        // 检查事件是否发生在列表的视口区域（viewport）
        if (watched == this->viewport()) {
            if (event->type() == QEvent::Enter) {
                // 鼠标进入：按需显示垂直滚动条
                this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            } else if (event->type() == QEvent::Leave) {
                // 鼠标离开：永久隐藏垂直滚动条
                this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            }
        }

        // 处理鼠标滚轮事件，优化滚动手感
        if (watched == this->viewport() && event->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
            // angleDelta().y() 返回滚轮滚动的角度（正值向上，负值向下）
            int numDegrees = wheelEvent->angleDelta().y() / 8;
            int numSteps = numDegrees / 15; // 计算标准滚动步数

            // 手动调整滚动条数值，控制滚动灵敏度
            this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numSteps);

            return true; // 拦截事件，不再向下传递
        }

        return QListWidget::eventFilter(watched, event);
    }

private:
    /**
     * 等待状态处理：
     * 当正在向服务器请求搜索结果时，显示 Loading 等待框，防止用户重复操作
     */
    void waitPending(bool pending = true);

    bool _send_pending;                  // 标记是否正处于请求等待状态
    void addTipItem();                   // 添加提示性条目（如“未找到相关结果”）

    std::shared_ptr<QDialog> _find_dlg;  // 使用智能指针管理搜索详情对话框
    QWidget* _search_edit;               // 关联的搜索输入框指针
    LoadingDlg * _loadingDialog;         // 加载中动画对话框指针

private slots:
    void slot_item_clicked(QListWidgetItem *item);     // 列表条目被点击槽函数
    void slot_user_search(std::shared_ptr<SearchInfo> si); // 收到搜索结果数据时的更新槽函数

signals:
         // 此处可以定义如跳转到用户详情等信号
     void sig_jump_chat_item(std::shared_ptr<SearchInfo> si);
};

#endif // SEARCHLIST_H
