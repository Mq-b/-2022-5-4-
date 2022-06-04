#include "subwindows.h"
#include "ui_subwindows.h"

SubWindows::SubWindows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubWindows)
{
    ui->setupUi(this);
}

SubWindows::~SubWindows()
{
    qDebug()<<"我是Subwindows,我被析构了...";
    delete ui;
}
