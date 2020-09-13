/********************************************************************************
** Form generated from reading UI file 'msgbox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGBOX_H
#define UI_MSGBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgBox
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget;

    void setupUi(QDialog *MsgBox)
    {
        if (MsgBox->objectName().isEmpty())
            MsgBox->setObjectName(QString::fromUtf8("MsgBox"));
        MsgBox->setWindowModality(Qt::WindowModal);
        MsgBox->resize(400, 200);
        MsgBox->setStyleSheet(QString::fromUtf8("background-color: rgb(22, 0, 136);\n"
"font: 16pt \"\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(MsgBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(240, 130, 81, 41));
        pushButton_2 = new QPushButton(MsgBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(104, 130, 81, 41));
        label = new QLabel(MsgBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 60, 301, 51));
        label->setStyleSheet(QString::fromUtf8("font: 18pt \"\351\273\221\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        label_2 = new QLabel(MsgBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 161, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\256\213\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        widget = new QWidget(MsgBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 400, 200));
        widget->raise();
        pushButton->raise();
        pushButton_2->raise();
        label->raise();
        label_2->raise();

        retranslateUi(MsgBox);

        QMetaObject::connectSlotsByName(MsgBox);
    } // setupUi

    void retranslateUi(QDialog *MsgBox)
    {
        pushButton->setText(QCoreApplication::translate("MsgBox", "\345\217\226\346\266\210", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MsgBox", "\347\241\256\345\256\232", nullptr));
        (void)MsgBox;
    } // retranslateUi

};

namespace Ui {
    class MsgBox: public Ui_MsgBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGBOX_H
