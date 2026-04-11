#include "textbubble.h"

#include <QFontMetricsF>
#include <QDebug>
#include <QFont>
#include "global.h"
#include <QTimer>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextLayout>
#include <QFont>

TextBubble::TextBubble(ChatRole role, const QString &text, QWidget *parent)
    :BubbleFrame(role,parent)
{
    m_pTextEdit=new QTextEdit();
    m_pTextEdit->setReadOnly(true);
    m_pTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTextEdit->installEventFilter(this);
    QFont font("Microsoft YaHei");
    font.setPointSize(12);
    m_pTextEdit->setFont(font);
    setPlainText(text);
    setWidget(m_pTextEdit);
    initStyleSheet();
}

bool TextBubble::eventFilter(QObject *o, QEvent *e)
{
    if(m_pTextEdit==o&&e->type()==QEvent::Paint){
        adjustTextHeight();
    }
    return BubbleFrame::eventFilter(o,e);
}

void TextBubble::adjustTextHeight()
{
    qreal doc_margin=m_pTextEdit->document()->documentMargin();
    QTextDocument*doc=m_pTextEdit->document();
    qreal text_height=0;
    //每一段高度相加等于文本高
    for(QTextBlock it=doc->begin();it!=doc->end();it=it.next()){
        QTextLayout*pLayout=it.layout();
        QRectF text_rect=pLayout->boundingRect();
        text_height+=text_rect.height();
    }
    int vMargin=this->layout()->contentsMargins().top();
    setFixedHeight(text_height+doc_margin*2+vMargin*2);
}

void TextBubble::setPlainText(const QString &text)
{
    m_pTextEdit->setPlainText(text);
    //找到最大宽度
    qreal doc_margin=m_pTextEdit->document()->documentMargin();
    int margin_left=this->layout()->contentsMargins().left();
     int margin_right=this->layout()->contentsMargins().right();
    QFontMetricsF fm(m_pTextEdit->font());
     QTextDocument *doc=m_pTextEdit->document();
    int max_width=0;
     //遍历每一段找到最宽的一段
    for(QTextBlock it=doc->begin();it!=doc->end();it=it.next()){
        int txtW=int(fm.horizontalAdvance(it.text()));
        max_width=std::max(max_width,txtW);
    }
    //设置气泡的最大宽度
    setMaximumWidth(max_width+doc_margin*2+(margin_left+margin_right));
}

void TextBubble::initStyleSheet()
{

}
