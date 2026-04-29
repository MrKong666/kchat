#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QList>
// #include "statelabel.h"
#include "global.h"
#include "statewidget.h"
#include <memory>
#include "userdata.h"
#include <QListWidgetItem>
namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
    void addChatUserList();
    void ClearLabelState(StateWidget*lb);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override ;
    void handleGlobalMousePress(QMouseEvent *event) ;
    void CloseFindDlg();
private:
    void ShowSearch(bool bsearch=false);
    void AddLBGroup(StateWidget*lb);
    Ui::ChatDialog *ui;
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
    QList<StateWidget*>_lb_list;
public slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_changed(const QString &str);
    void slot_apply_friend(std::shared_ptr<AddFriendApply> apply);
};

#endif // CHATDIALOG_H
