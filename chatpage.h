#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();
protected:
    void paintEvent(QPaintEvent*event);
private slots:
    void on_receive_btn_clicked();
    void on_send_btn_clicked();
    void on_title_lb_linkActivated(const QString &link);

private:
    Ui::ChatPage *ui;
};

#endif // CHATPAGE_H
