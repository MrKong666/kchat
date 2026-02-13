/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"
#include "timerbtn.h"

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout;
    QLabel *user_label;
    QLineEdit *user_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *email_label;
    QLineEdit *email_lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pass_label;
    QLineEdit *pass_Edit;
    ClickedLabel *pass_visible;
    QHBoxLayout *horizontalLayout_4;
    QLabel *confirm_label;
    QLineEdit *confirm_Edit;
    ClickedLabel *confirm_visible;
    QHBoxLayout *horizontalLayout_5;
    QLabel *verify_label;
    QLineEdit *verify_lineEdit;
    TimerBtn *get_code;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *sure_pushButton;
    QPushButton *cancel_pushButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_4;
    QLabel *tip_lb;
    QLabel *tip2_lb;
    QSpacerItem *verticalSpacer_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *return_btn;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(300, 500);
        RegisterDialog->setMinimumSize(QSize(300, 500));
        RegisterDialog->setMaximumSize(QSize(300, 500));
        verticalLayout_2 = new QVBoxLayout(RegisterDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        widget = new QWidget(page);
        widget->setObjectName("widget");
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        err_tip = new QLabel(widget);
        err_tip->setObjectName("err_tip");
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(err_tip);


        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        user_label = new QLabel(page);
        user_label->setObjectName("user_label");
        user_label->setMinimumSize(QSize(0, 25));
        user_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_label);

        user_lineEdit = new QLineEdit(page);
        user_lineEdit->setObjectName("user_lineEdit");
        user_lineEdit->setMinimumSize(QSize(0, 25));
        user_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_lineEdit);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        email_label = new QLabel(page);
        email_label->setObjectName("email_label");
        email_label->setMinimumSize(QSize(0, 25));
        email_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(email_label);

        email_lineEdit = new QLineEdit(page);
        email_lineEdit->setObjectName("email_lineEdit");
        email_lineEdit->setMinimumSize(QSize(0, 25));
        email_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(email_lineEdit);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pass_label = new QLabel(page);
        pass_label->setObjectName("pass_label");
        pass_label->setMinimumSize(QSize(0, 25));
        pass_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(pass_label);

        pass_Edit = new QLineEdit(page);
        pass_Edit->setObjectName("pass_Edit");
        pass_Edit->setMinimumSize(QSize(0, 25));
        pass_Edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(pass_Edit);

        pass_visible = new ClickedLabel(page);
        pass_visible->setObjectName("pass_visible");
        pass_visible->setMinimumSize(QSize(20, 20));
        pass_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_3->addWidget(pass_visible);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        confirm_label = new QLabel(page);
        confirm_label->setObjectName("confirm_label");
        confirm_label->setMinimumSize(QSize(0, 25));
        confirm_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(confirm_label);

        confirm_Edit = new QLineEdit(page);
        confirm_Edit->setObjectName("confirm_Edit");
        confirm_Edit->setMinimumSize(QSize(0, 25));
        confirm_Edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(confirm_Edit);

        confirm_visible = new ClickedLabel(page);
        confirm_visible->setObjectName("confirm_visible");
        confirm_visible->setMinimumSize(QSize(20, 20));
        confirm_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(confirm_visible);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verify_label = new QLabel(page);
        verify_label->setObjectName("verify_label");
        verify_label->setMinimumSize(QSize(0, 25));
        verify_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(verify_label);

        verify_lineEdit = new QLineEdit(page);
        verify_lineEdit->setObjectName("verify_lineEdit");
        verify_lineEdit->setMinimumSize(QSize(0, 25));
        verify_lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(verify_lineEdit);

        get_code = new TimerBtn(page);
        get_code->setObjectName("get_code");
        get_code->setMinimumSize(QSize(0, 25));
        get_code->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(get_code);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        sure_pushButton = new QPushButton(page);
        sure_pushButton->setObjectName("sure_pushButton");
        sure_pushButton->setMinimumSize(QSize(0, 25));
        sure_pushButton->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(sure_pushButton);

        cancel_pushButton = new QPushButton(page);
        cancel_pushButton->setObjectName("cancel_pushButton");
        cancel_pushButton->setMinimumSize(QSize(0, 25));
        cancel_pushButton->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(cancel_pushButton);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        tip_lb = new QLabel(page_2);
        tip_lb->setObjectName("tip_lb");
        tip_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(tip_lb);

        tip2_lb = new QLabel(page_2);
        tip2_lb->setObjectName("tip2_lb");
        tip2_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(tip2_lb);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        widget_2 = new QWidget(page_2);
        widget_2->setObjectName("widget_2");
        horizontalLayout_7 = new QHBoxLayout(widget_2);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        return_btn = new QPushButton(widget_2);
        return_btn->setObjectName("return_btn");
        return_btn->setMinimumSize(QSize(0, 25));
        return_btn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(return_btn);

        horizontalSpacer = new QSpacerItem(75, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout_5->addWidget(widget_2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Dialog", nullptr));
        err_tip->setText(QCoreApplication::translate("RegisterDialog", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        user_label->setText(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267:", nullptr));
        email_label->setText(QCoreApplication::translate("RegisterDialog", "\351\202\256\347\256\261:", nullptr));
        pass_label->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201:", nullptr));
        pass_visible->setText(QString());
        confirm_label->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244\345\257\206\347\240\201:", nullptr));
        confirm_visible->setText(QString());
        verify_label->setText(QCoreApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201:", nullptr));
        get_code->setText(QCoreApplication::translate("RegisterDialog", "\350\216\267\345\217\226", nullptr));
        sure_pushButton->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244", nullptr));
        cancel_pushButton->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
        tip_lb->setText(QCoreApplication::translate("RegisterDialog", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\2145s\345\220\216\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
        tip2_lb->setText(QCoreApplication::translate("RegisterDialog", "\345\217\257\347\202\271\345\207\273\350\277\224\345\233\236\346\214\211\351\222\256\347\233\264\346\216\245\350\277\224\345\233\236\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        return_btn->setText(QCoreApplication::translate("RegisterDialog", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
