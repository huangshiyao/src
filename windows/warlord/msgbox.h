#ifndef MSGBOX_H
#define MSGBOX_H

#include <list>
#include <QDialog>
#include "ui_msgbox.h"

using namespace std;

class MsgBox : public QDialog
{
    Q_OBJECT

public:
    enum Type
    {
        info,
        alert
    };
    static void throwBox(const QString &msg, Type type = info);
    static bool catchBox(const QString &msg, Type type = info);

private:
    explicit MsgBox(int btn, QWidget *parent = nullptr);
    ~MsgBox();
    Ui::MsgBox ui;
    void setMsg(const QString &msg, Type type);
};

#endif // MSGBOX_H
