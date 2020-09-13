#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>
#include <QList>
#include "ui_msgbox.h"

class MsgBox : public QDialog
{
    Q_OBJECT

public:
    enum msgType
    {
        info,
        alert
    };
    static void pop(const QString &msg, msgType type = info);
    static bool wait();
private:
    explicit MsgBox(QWidget *parent = nullptr);
    ~MsgBox();
    Ui::MsgBox ui;
    void setMsg(const QString &msg, msgType type);
    bool access;

    static QList<MsgBox *> ls;
    static MsgBox *act();
};

#endif // MSGBOX_H
