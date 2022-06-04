#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //测试
    int value=dataplus(10,20).toInt();
    QString str=dataplus("hello","word").toString();
    qDebug()<<value;
    qDebug()<<str;

    //创建Person对象
    Person p;
    p.id=250;
    p.name="张三";

    //两种存入方式
#if 0
    QVariant v;
    v.setValue(p);
#else
    QVariant v= QVariant::fromValue(p);
#endif

    //取出对象中的数据
    if(v.canConvert<Person>())
    {
        Person tmp = v.value<Person>();
        qDebug()<<"id:"<<tmp.id<<", name:"<<tmp.name;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVariant MainWindow::dataplus(QVariant a,QVariant b)
{
    QVariant ret;
    //判断当前参数的类型是字符串还是整形数
    if(a.type()==QVariant::Int && b.type()==QVariant::Int)
    {
        ret=QVariant(a.toInt()+b.toInt());
    }
    else if(a.type()==QVariant::String && b.type()==QVariant::String)
    {
        ret.setValue(a.toString()+b.toString());
    }
    return ret;
}
