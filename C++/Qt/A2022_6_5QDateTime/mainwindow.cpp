#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //获取当前日期
    QDate d = QDate::currentDate();
    //第一种方式
    qDebug()<<"year:"<<d.year()<<",month:"<<d.month()<<",day:"<<d.day();

    //第二种方式
    QString str=d.toString("yyyy-MM-dd");
    qDebug()<<str;

#if 0
    //获取当前时间
    QTime s=QTime::currentTime();
    //方式一
    qDebug()<<s.hour()<<':'<<s.minute()<<':'<<s.second()<<'.'<<s.msec();
    //方式二
    QString strm=s.toString("hh:mm:ss.zzz");
    qDebug()<<strm;
#else
#endif
    //统计函数运行时间  由于QTime的start与elapsed被弃用 使用QElapsedTimer
    QElapsedTimer tt;
    tt.start();
    randNumbers(100);
    int ms=tt.elapsed();
    qDebug()<<"函数运行时间是:"<<ms<<"毫秒";


    //获取当前的日期和时间
    QDateTime dt = QDateTime::currentDateTime();
    //格式化 2020/01/10 12:12:12 上午/下午
    //  yyyy/MM/dd hh:mm:ss ap
    QString strdt = dt.toString("yyyy/mm/dd hh:mm:ss ap");
    qDebug()<<"当前的你日期和时间"<<strdt;

    //先取出日期
    d=dt.date();
    qDebug()<<d.year()<<d.month()<<d.day();
    //取出时间
    QTime t = dt.time();
    qDebug()<<t.hour()<<t.minute()<<t.second();
}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::randNumbers(int count)
{
    srand(time(NULL));
    for(int i=0;i<count;++i)
    {
        int num = rand()%10000;
        qDebug()<<num;
    }
}
