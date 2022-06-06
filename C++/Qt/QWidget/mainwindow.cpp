#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mydialog.h"
#include <QPoint>
#include <QRect>
#include<QDebug>
#include <QMenu>
#include<QMessageBox>
#include<QFileDialog>
#include<QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //值得注意的是QWidget可以被任何子类继承 所有的控件类 例如QDialog   QmainWindow等都可以直接使用它的API


    //设置窗口的最大尺寸
    //setMaximumSize(600,300);
    //设置窗口的最小尺寸
    //setMinimumSize(300,300);
    //设置窗口的固定尺寸
    //setFixedSize(500,500);
    //设置窗口标题
    setWindowTitle("helo QT");
    //给显示窗口设置图标
    setWindowIcon(QIcon("D:\\素材！！！！！！！！！！！！\\1 (67).jpg"));

    //最大和最小尺寸表示可以在这个尺寸内进行拉伸 不能大于也不能小于 这个尺寸是不包含标题栏的
    //最大最小尺寸和固定尺寸是冲突的 固定尺寸是无法拉伸的 选择一个即可

    //我们下面通过按钮 信号槽的方式演示了其他方法

    //图标发生变化时发射此信号&MainWindow::windowTitleChanged       函数的参数是因为会返回新标题的名字
    connect(this,&MainWindow::windowTitleChanged,this,[=](const QString &title)
    {
        qDebug()<<"新的标题:"<<title;
    });
    //窗口发生变化的时候发射此信号                        返回的图标类型是QIcon
    connect(this,&MainWindow::windowIconChanged,this,[=](const QIcon &icon)
    {
        qDebug()<<"当前图标被修改了...";
    });

    //声明右键菜单的策略   右击的时候就会发射出信号
    setContextMenuPolicy(Qt::CustomContextMenu);//https://doc.qt.io/qt-5/qt.html#ContextMenuPolicy-enum     对其传入参数有介绍
    connect(this,&MainWindow::customContextMenuRequested,this,[=](const QPoint &pos)//此信号会返回一个Qpoint类型 也就是一个坐标
    {
        //创建菜单对象 推荐菜单项
        QMenu menu;
        menu.addAction("西红柿");
        menu.addAction("黄瓜");
        menu.addAction("茄子");
        //默认情况菜单不显示 我们需要调用exec方法 它的参数就是我们当前光标所在的位置
        menu.exec(QCursor::pos());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//移动窗口
void MainWindow::on_moveBtn_clicked()
{
    QRect rect = this->frameGeometry();//获取当前的坐标
    move(rect.topLeft()+QPoint(10,20));//移动 相当于一直是往右下移动
}

//获取位置信息
void MainWindow::on_positionBtn_clicked()
{
    QRect rect = this->frameGeometry();
    qDebug()<<"左上角:"<<rect.topLeft()
            <<"右上角:"<<rect.topRight()
            <<"左下角:"<<rect.bottomLeft()
            <<"右下角:"<<rect.bottomRight()
            <<"宽度:"<<rect.width()
            <<"高度:"<<rect.height();
}

//修改窗口的位置和尺寸信息(位置随机)
void MainWindow::on_geometryBtn_clicked()
{
    int x = 100+ rand()%500;
    int y= 100+ rand()%500;
    int width=this->width()+10;
    int height=this->height()+10;
    setGeometry(x,y,width,height);
}

//更换标题和图标
void MainWindow::on_pushButton_clicked()
{
    setWindowTitle("你好世界");
    setWindowIcon(QIcon("D:\\素材！！！！！！！！！！！！\\QQ图片20220606103852.jpg"));
}

//显示模态对话框和判断
void MainWindow::on_modalDlg_clicked()
{
    MyDialog dlg;
    connect(&dlg,&MyDialog::finished,this,[=](int res){
        qDebug()<<"resukt:"<<res;
    });
    connect(&dlg,&MyDialog::accepted,this,[=](){
        qDebug()<<"accepted 信号被发射了...";
    });
    connect(&dlg,&MyDialog::rejected,this,[=](){
        qDebug()<<"rejected 信号被发射了...";
    });

    //写了上面的信号后下面这段不会被执行
    int ret = dlg.exec();//显示模态对话框

    if(ret==QDialog::Accepted)
    {
        qDebug()<<"accept button clicked...";
    }
    else if(ret==QDialog::Rejected)
    {
        qDebug()<<"reject button clicked...";
    }
    else
    {
        qDebug()<<"done button clicked...";
    }
}

void MainWindow::on_msgbox_clicked()
{
    QMessageBox::about(this,"about","这是一个简单的消息提示~~");
    QMessageBox::critical(this,"critical","这是一个错误的对话框-critical...");//X号
    //第一个参数是接收者 第二个参数是窗口标题 第三参数是窗口显示的文本 第四个参数是分别表示两个选项 同时点击的话会返回相对应的参数 第五个参数是表示默认焦点在哪个按钮上
    //也可以不写 那么默认第一个按钮
    int ret = QMessageBox::question(this,"question","你要保存修改的文件内容吗???",//?号
                                    QMessageBox::Save | QMessageBox::Cancel,QMessageBox::Cancel);

    if(ret==QMessageBox::Save)
    {
        QMessageBox::information(this,"information","恭喜你保存成功了(*^▽^*)!!!");//!号
    }
    else if(ret ==QMessageBox::Cancel)
    {
        QMessageBox::warning(this,"warning","你放弃了保存o(╥﹏╥)o!!!");//!号
    }
}

void MainWindow::on_filedlg_clicked()
{
#if 0   //第一种 它只能打开目录
    QString dirName = QFileDialog::getExistingDirectory(this,"打开目录","D:\\自用");//默认打开的目录 然后我们可以自己选择
    QMessageBox::information(this,"打开目录","您选择的目录是:"+dirName);//弹窗 显示我们打开的目录
#endif

#if 0   //第二种 它能打开文件
    QString arg("Text files (*.txt)");
    //初始化过滤器 有两种选择 默认是arg的Text    最后返回打开文件的绝对路径
    QString fileName=QFileDialog::getOpenFileName(
                this,tr("OPen FIle"),"D://自用",
                tr("Images9(*.png *.jpg);;Text files (*.txt)"),&arg);
    //打印显示
    QMessageBox::information(this,"打开文件","您选择的文件夹是:"+fileName);
#endif

#if 0   //第三种 它能打开多个文件遍历
    //这里由于于没有创建arg 也就不是没有默认值 而是第一个Images9 同时QStringList相当于有一堆QString的列表
    QStringList fileNames=QFileDialog::getOpenFileNames(//getOpenFileNames和上面那个相比只是多了一个s 但是返回的类型变成了QStringList
                this,tr("OPen FIle"),"D://自用",
                tr("Images9(*.png *.jpg);;Text files (*.txt)"));
    QString names;
    for(int i=0;i<fileNames.size();++i)
    {
        names+=fileNames[i]+"\n";
    }
    QMessageBox::information(this,"打开文件(s)","您选择的文件夹是:"+names);
#endif

#if 1   //第四种 用来覆盖已有文件 或者自己写一个文件 不过这些都是不存在的 这个对话框只是用来找路径的
    QString fileName=QFileDialog::getSaveFileName(this,"保存的文件","D:\\");
    QMessageBox::information(this,"保存文件","您指定的保存数据的文件是:"+fileName);

#endif
}

