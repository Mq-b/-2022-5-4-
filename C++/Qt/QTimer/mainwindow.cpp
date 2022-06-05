#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include<QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建定时器
    QTimer* timer = new QTimer;

    //修改定时器对象的精度
    timer->setTimerType(Qt::PreciseTimer);

    //按钮的点击事件
    connect(ui->loopBtn,&QPushButton::clicked,this,[=]()
    {
        //启动计时器
        if(timer->isActive())
        {
            timer->stop();  //关闭定时器
            ui->loopBtn->setText("开始");
        }
        else
        {
            ui->loopBtn->setText("关闭");
            timer->start(1000); //1000ms == 1s
        }
    });
    connect(timer,&QTimer::timeout,this,[=]()
    {
        QTime tm = QTime::currentTime();
        //格式化当前得到的系统时间
        QString tmstr = tm.toString("hh:mm:ss.zzz");
        ui->curTime->setText(tmstr);
    });

    //发射一次信号
    connect(ui->onceBtn,&QPushButton::clicked,this,[=]()
    {
        //获取两秒以后的系统时间
       QTimer::singleShot(2000,this,[=]()
       {
           QTime tm = QTime::currentTime();
           //格式化当前得到的系统时间
           QString tmstr = tm.toString("hh:mm:ss.zzz");
           //设置要显示的时间
           ui->onceTime->setText(tmstr);
       });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
