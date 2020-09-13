#include "maingui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainGui w;


    if(a.exec())
        return 1;

    return 0;
}
