#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H
/**
 * @file messagetextedit.h
 * @brief  气泡聊天
 *
 * @date  2026/04/07
 * @author 孔祥锐
 */

#include<QObject>
#include<QTextEdit>
#include<QMouseEvent>
#include<QApplication>
#include<QDrag>
#include<QMimeData>
#include<QMimeType>
#include<QFileInfo>
#include<QFileIconProvider>
#include<QPainter>
#include<QVector>
#include"global.h"
class MessageTextEdit :public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageTextEdit(QWidget* parent=nullptr);
    ~MessageTextEdit();

    QVector<MsgInfo>getMsgList();
    void insertFileFromUrl(const QStringList& urls);
signals:
    void send();
protected:
    void dragEnterEvent(QDragEnterEvent*event);
    void dropEvent(QDropEvent* event);
    void keyPressEvent(QKeyEvent*e);
private:
    void insertImages(const  QString &url);
    void insertTextFile(const QString&url);
    bool canInsertFromMimeData(const QMimeData*source)const;
    void insertFromMimeData(const QMimeData*source);

    bool isImage(QString url);//判断文件是否为图片
    void insertMsgList(QVector<MsgInfo>&list,QString flag,QString text,QPixmap pix);

    QStringList getUrl(QString text);

    QPixmap getFileIconPixmap(const QString&url);//获取文件图标和大小信息，并转换为图片

    QString getFileSize(qint64 size);//获取文件大小

private slots:
    void textEditChanged();

private:
    QVector<MsgInfo> mMsgList;
    QVector<MsgInfo> mGetMsgList;
};

#endif // MESSAGETEXTEDIT_H
