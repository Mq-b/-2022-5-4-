#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"testwidget.h"
#include"testdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //一般在qt的构造函数中进行初始化操作
    //显示当前窗口的时候 显示另一个窗口 TestWidget
#if 1
    //创建窗口对象 没有new给w对象指定父类对象 这个窗口就是一个独立窗口
    //要显示窗口就必须show
    TestWidget*w = new TestWidget;
    //显示当前窗口
    w->show();
#else
    //创建窗口对象    窗口被内嵌在一起了
    //如果创建窗口对象的时候指定了父对象 这个窗口就不是一个独立窗口
    //这样的话当前父窗口显示的时候 子窗口被一并显示出来了
    //这时候子窗口是没有边框的
    TestWidget * w= new TestWidget(this);
#endif

#if 0
    //创建对话框窗口
    TestDialog * dig = new TestDialog(this);
    //非模态
    dig->show();
#else
    //创建对话窗口
    TestDialog*dlg = new TestDialog(this);
    //模态 exec()
    //阻塞程序的执行
    dlg->exec();
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

