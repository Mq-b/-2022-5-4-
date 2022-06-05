#ifndef ME_H
#define ME_H

#include <QObject>

class Me : public QObject
{
    Q_OBJECT
public:
    explicit Me(QObject *parent = nullptr);

public slots:
    void eat();

};

#endif // ME_H
