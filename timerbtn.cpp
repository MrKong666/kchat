#include "timerbtn.h"
#include<QDebug>
#include<QMouseEvent>
TimerBtn::TimerBtn(QWidget* parent):QPushButton(parent),_counter(10)
{
    _timer=new QTimer(this);
    connect(_timer,&QTimer::timeout,[this](){
        _counter--;
        if(_counter<=0){
            _timer->stop();
            _counter=10;
            this->setText("获取");
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(_counter));
    });
}

TimerBtn::~TimerBtn()
{
    _timer->stop();
}

void TimerBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        //在这里处理鼠标左键释放按键
        qDebug()<<"MyButton was release!";
        this->setEnabled(false);
        this->setText(QString::number(_counter));
        _timer->start(1000);
        emit clicked();
    }
    //调用父类函数完成其他事件处理
    QPushButton::mouseMoveEvent(e);
}
