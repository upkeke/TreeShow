#include "mainwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //qDebug("0x0f = %d", 0x0f);
    QApplication a(argc, argv);
    MainWin w;

    w.show();
    return a.exec();
}
