#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_me = new Me;
    m_girl = new GirlFriend;
    //信号绑定eat函数
    connect(m_girl,&GirlFriend::hungry,m_me,&Me::eat);
    //使用this 当前类方法接收信号后的执行动作    意味着当前hungry这个信号关联了两个函数
    connect(m_girl,&GirlFriend::hungry,this,&MainWindow::eatSlot);
    //信号连接槽函数
    //connect(ui->hungry,&QPushButton::clicked,this,&MainWindow::hungrySlot);
    /*hungry按钮被点击后就发射QPushButton的clicked信号 由this也就是当前窗口接收 执行槽函数hungrySlot
    然后发射自定义信号hungry 发射信号之后右被检测到了 调用Me对象的eat方法 执行  也就是13行的代码*/

    //信号之间连接信号  相当于第17行那种方式的简化
    //connect(ui->hungry,&QPushButton::clicked,m_girl,&GirlFriend::hungry);

    //使用lambda表达式 匿名函数作为接收信号后的执行 由于不是哪个类成员函数 所以可以少写一个参数
    connect(ui->hungry,&QPushButton::clicked,[]{qDebug()<<"无趣";});

    //信号发出者     发出的信号       信号的接受者      接收后执行的动作
    //如果信号不发出 那么就永远没有动作 这里是关闭窗口 使用的自带的信号
    connect(ui->closeBtn,&QPushButton::clicked,this,&MainWindow::close);

    //直接触发信号    信号触发后会执行被关联的方法
    //m_girl->hungry();

    //断开信号  用的很少
    //disconnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hungrySlot()
{
    //发射自定义信号   emit加不加无所谓  这里是调用的第13行的信号
    emit m_girl->hungry();
}

void MainWindow::eatSlot()
{
    qDebug()<<"我带你去吃海鲜...";
}
