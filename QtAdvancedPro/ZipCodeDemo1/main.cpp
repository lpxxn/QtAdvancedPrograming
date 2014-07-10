#include "mainwindow.h"
#include <QApplication>

#include <QString>
#include <QDebug>

#include <QRect>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QString str=QString("aa %L1").arg(123456,0,10);
    qDebug()<<str;

    QRect rect(0,0,50,50);
    qDebug()<<rect;
    rect.adjust(0,0,-10,0);
    qDebug()<<rect;
    return a.exec();
}
