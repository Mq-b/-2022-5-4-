#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDate>
#include<QDebug>
#include<QTime>
#include <QElapsedTimer>
#include<QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void randNumbers(int count);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
