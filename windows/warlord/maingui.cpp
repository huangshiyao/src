#include <map>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include "maingui.h"
#include "msgbox.h"

MainGui::MainGui(QWidget *parent)
    : QWidget(parent),
      map()
{
    //setWindowFlags(Qt::FramelessWindowHint);  //禁用边框及控件
    ui.setupUi(this);
    foreach_widget_get(this);
    resize(800, 600);
    show();
    connect(ui.pushButton, &QPushButton::clicked, [&]{if(MsgBox::catchBox("确定关闭？")) close();});
}

MainGui::~MainGui()
{
}

void MainGui::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setWindow(-320, -240, 640, 480);
    painter.scale(1, 1);
    painter.setPen(QColor(255, 0, 0));
    painter.setBrush(QColor(255, 0, 0));
    painter.drawRect(-160, -120, 320, 240);

}

void MainGui::resizeEvent(QResizeEvent *event)
{
    QSize size(event->size().width(), event->size().height());
    foreach_widget_set(size, this);
}

void MainGui::foreach_widget_get(QWidget *w)
{
    QRect *rect=new QRect();
    rect->setX(w->x());
    rect->setY(w->y());
    rect->setWidth(w->width());
    rect->setHeight(w->height());
    map.insert(w, *rect);
    const QObjectList &ls=w->children();
    if(!ls.isEmpty())
    {
        for(auto i=ls.begin(); i<ls.end(); i++)
        {
            if((*i)->isWidgetType())
                foreach_widget_get((QWidget *)*i);
        }
    }
}

void MainGui::foreach_widget_set(QSize size, QWidget *w)
{
    w->resize(size.width(), size.height());
    const QObjectList &ls=w->children();
    if(!ls.isEmpty())
    {
        double kx=(double)size.width()/(*map.find(w)).width();
        double ky=(double)size.height()/(*map.find(w)).height();
        for(auto i=ls.begin(); i<ls.end(); i++)
        {
            if((*i)->isWidgetType())
            {
                QWidget *child=(QWidget *)*i;
                int x=map.find(child)->x();
                int y=map.find(child)->y();
                int w=map.find(child)->width();
                int h=map.find(child)->height();
                child->move(x*kx, y*ky);
                foreach_widget_set(QSize(w*kx, h*ky), child);
            }
        }
    }
}
