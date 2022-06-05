#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_me = new Me;
    m_girl = new GirlFriend;

    connect(m_girl,&GirlFriend::hungry,m_me,&Me::eat);
    connect(ui->hungry,&QPushButton::clicked,this,&MainWindow::hungrySlot);
    /*hungry按钮被点击后就发射QPushButton的clicked信号 由this也就是当前窗口接收 执行槽函数hungrySlot
    然后发射自定义信号hungry 发射信号之后右被检测到了 调用Me对象的eat方法 执行  也就是13行的代码*/

    //信号发出者     发出的信号       信号的接受者      接收后执行的动作
    //如果信号不发出 那么就永远没有动作
    connect(ui->closeBtn,&QPushButton::clicked,this,&MainWindow::close);

    //单独触发信号
    m_girl->hungry();
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
