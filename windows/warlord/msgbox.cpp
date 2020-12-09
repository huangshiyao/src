#include <list>
#include <QPushButton>
#include "msgbox.h"
#include "ui_msgbox.h"

using namespace std;

MsgBox::MsgBox(int btn, QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);  //禁用对话框边框及控件
    setAttribute(Qt::WA_TranslucentBackground);  //背景透明
    ui.setupUi(this);

    if(btn==1)
    {
        ui.pushButton->close();
        ui.pushButton_2->move(160, ui.pushButton_2->y());
        connect(ui.pushButton_2, &QPushButton::clicked, this, &MsgBox::close);
    }
    if(btn==2)
    {
        connect(ui.pushButton_2, &QPushButton::clicked, this, &QDialog::accept);
        connect(ui.pushButton, &QPushButton::clicked, this, &QDialog::reject);
    }
}

MsgBox::~MsgBox()
{
}

void MsgBox::setMsg(const QString &msg, Type type)
{
    if(type==alert)
        ui.label_2->setText("！警告");
    if(type==info)
        ui.label_2->setText("？提示");
    ui.label->setText(msg);
}

void MsgBox::throwBox(const QString &msg, Type type)
{
    MsgBox box(1, QApplication::activeWindow());
    box.setMsg(msg, type);
    box.exec();
}

bool MsgBox::catchBox(const QString &msg, Type type)
{
    MsgBox box(2, QApplication::activeWindow());
    box.setMsg(msg, type);
    if(box.exec()==QDialog::Accepted)
        return true;
    else
        return false;
}
