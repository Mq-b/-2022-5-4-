#include "mainwindow.h"
#include<QDebug>
#include <QApplication>
#include<QByteArray>
#include<QString>
int main(int argc, char *argv[])
{
    QByteArray array(10,'a');
    array.setNum(125.6);
    for(int i=0;i<array.size();i++){
        qDebug()<<array[i];
    }
    qDebug()<<array;
    QString str="1234";
    bool choose;
    int s=str.toInt(&choose,10);
    qDebug()<<s;
    qDebug()<<choose;

    QString Str=QString("离谱离谱(%1)，还有更离谱的(%2)，或者说你(%3)").arg("唐僧").arg("沙僧").arg("老王");
    qDebug()<<Str;
    qDebug()<<Str.size();
    qDebug()<<Str.length();
    //字符串拼接
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
