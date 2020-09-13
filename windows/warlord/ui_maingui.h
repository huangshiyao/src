/********************************************************************************
** Form generated from reading UI file 'maingui.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGUI_H
#define UI_MAINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGui
{
public:
    QPushButton *pushButton;
    QWidget *widget;
    QPushButton *pushButton_2;

    void setupUi(QWidget *MainGui)
    {
        if (MainGui->objectName().isEmpty())
            MainGui->setObjectName(QString::fromUtf8("MainGui"));
        MainGui->resize(640, 480);
        MainGui->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        pushButton = new QPushButton(MainGui);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(600, 10, 31, 31));
        pushButton->setStyleSheet(QString::fromUtf8("font: 75 10pt \"ADMUI3Lg\";\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(77, 77, 77);"));
        widget = new QWidget(MainGui);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 281, 211));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 0);"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(70, 60, 131, 81));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 16pt \"\351\273\221\344\275\223\";\n"
"background: none;"));

        retranslateUi(MainGui);

        QMetaObject::connectSlotsByName(MainGui);
    } // setupUi

    void retranslateUi(QWidget *MainGui)
    {
        MainGui->setWindowTitle(QCoreApplication::translate("MainGui", "MainGui", nullptr));
        pushButton->setText(QCoreApplication::translate("MainGui", "X", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainGui", "\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGui: public Ui_MainGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGUI_H
