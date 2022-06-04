#ifndef SUBWINDOWS_H
#define SUBWINDOWS_H
#include <QDialog>

namespace Ui {
class SubWindows;
}

class SubWindows : public QDialog
{
    Q_OBJECT

public:
    explicit SubWindows(QWidget *parent = nullptr);
    ~SubWindows();

private:
    Ui::SubWindows *ui;
};

#endif // SUBWINDOWS_H
