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

    //修改定时器对象的精度    在底层是枚举 有三种精度 我们这里使用的0试图保证毫秒的误差 1会试图使精确度保持在所需间隔的5%以内 2会只能保证秒级误差
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
            timer->start();
            //start方法还有一个重载void QTimer:: start ( int msec )
            //以msec毫秒的超时间隔启动或重新启动计时器。 也就是说 如果我写了1000作为参数 那么每次需要隔一秒 计时器才会重新被启动
            //如果计时器已经在运行，它将停止并重新启动。
            //timer->start(1000);//1000ms == 1s
        }
    });
    //timer如果想要触发这种信号 必须保证的是它计时器正在运行
    //timer是信号的发出者 然后它的timeout是发出的信号，它是根据时间的变化触发信号发射 然后this也就是当前进行接收  然后lambda就是执行的行为
    connect(timer,&QTimer::timeout,this,[=]()
    {
        QTime tm = QTime::currentTime();
        //格式化当前得到的系统时间
        QString tmstr = tm.toString("hh:mm:ss.zzz");
        ui->curTime->setText(tmstr);
    });

    //发射一次信号    点击一下按钮 触发lambda行为   
    connect(ui->onceBtn,&QPushButton::clicked,this,[=]()
    {
        //这个静态函数在一个给定时间间隔 msec(毫秒) 之后调用一个槽 不会重复调用。  目的:获取两秒以后的系统时间
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
