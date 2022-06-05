#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //x轴与y轴的坐标
    QLine line(QPoint(100,200),QPoint(150,200));
    //平移
    QLine newLine=line.translated(20,20);
    qDebug()<<"平移前的坐标点："<<line;
    qDebug()<<"平移后的坐标点："<<newLine;
}

MainWindow::~MainWindow()
{
    delete ui;
}
