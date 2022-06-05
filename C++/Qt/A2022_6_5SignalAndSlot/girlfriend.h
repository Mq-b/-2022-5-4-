#ifndef GIRLFRIEND_H
#define GIRLFRIEND_H

#include <QObject>

class GirlFriend : public QObject
{
    Q_OBJECT
public:
    explicit GirlFriend(QObject *parent = nullptr);

signals:
    void hungry();
};

#endif // GIRLFRIEND_H
