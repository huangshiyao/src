#ifndef MAINGUI_H
#define MAINGUI_H

#include <QWidget>
#include <QMap>
#include <QRect>
#include "ui_maingui.h"

class MainGui : public QWidget
{
    Q_OBJECT

public:
    MainGui(QWidget *parent = nullptr);
    ~MainGui();
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainGui ui;
    QMap<QWidget *, QRect> map;

    void foreach_widget_get(QWidget *w);
    void foreach_widget_set(QSize size, QWidget *w);
};
#endif // MAINGUI_H
