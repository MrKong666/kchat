#ifndef CLICKEDONCELABEL_H
#define CLICKEDONCELABEL_H
/**
 * @file clickedoncelabel.h
 * @brief  只点一次的标签
 *
 * @date  2026/04/08
 * @author 孔祥锐
 */

#include <QLabel>
#include <QMouseEvent>

class ClickedOnceLabel:public QLabel
{
    Q_OBJECT
public:
    ClickedOnceLabel(QWidget *parent=nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void clicked(QString );
};

#endif // CLICKEDONCELABEL_H
