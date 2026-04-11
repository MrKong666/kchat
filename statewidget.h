#ifndef STATEWIDGET_H
#define STATEWIDGET_H
/**
 * @file statewidget.h
 * @brief  *
 * StateWidget 类：支持状态切换的自定义控件
 * 功能：支持 6 种状态切换（常态、悬停、按下 以及 选中后的三态）
 * 额外功能：支持红点（未读消息提示）显示

 *
 * @date  2026/04/08
 * @author 孔祥锐
 */

#include <QWidget>
#include "global.h" // 包含全局定义，如 ClickLbState 枚举
#include <QLabel>


class StateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StateWidget(QWidget *parent = nullptr);

    /**
     * 设置不同状态下的样式表名称或图片路径
     * 参数对应：正常、悬停、按下、选中、选中悬停、选中按下
     */
    void SetState(QString normal="", QString hover="", QString press="",
                  QString select="", QString select_hover="", QString select_press="");

    ClickLbState GetCurState(); // 获取当前控件的状态（枚举值）
    void ClearState();          // 重置状态为初始常态

    void SetSelected(bool bselected); // 设置控件的选中状态（如点击导航栏后的高亮）
    void AddRedPoint();               // 在控件上初始化一个红点控件
    void ShowRedPoint(bool show=true); // 控制红点的显示或隐藏

protected:
    /**
     * 重写绘图事件：为了让 QSS 样式表在自定义 QWidget 上生效
     */
    void paintEvent(QPaintEvent* event);

    // 鼠标交互事件重写：用于实现点击、悬停等状态的切换逻辑
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;

private:
    // 基础状态对应的样式名/路径
    QString _normal;
    QString _normal_hover;
    QString _normal_press;

    // 选中状态下的样式名/路径
    QString _selected;
    QString _selected_hover;
    QString _selected_press;

    ClickLbState _curstate; // 记录当前的交互状态
    QLabel * _red_point;    // 红点标签（通常是一个小圆点图片或自绘圆圈）

signals:
    void clicked(void);     // 当鼠标松开且在控件范围内时触发的信号

public slots:
};

#endif // STATEWIDGET_H
