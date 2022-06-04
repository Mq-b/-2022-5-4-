#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"subwindows.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SubWindows* sub= new SubWindows(this);
    sub->show();    //非模态显示
}

MainWindow::~MainWindow()
{
    qDebug()<<"我是MainWindow,我被析构了...";
    delete ui;
}
