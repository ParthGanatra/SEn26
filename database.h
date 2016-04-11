#ifndef DATABASE_H
#define DATABASE_H



#include <QObject>
#include <QDebug>
#include <mongo/client/dbclient.h>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = 0);

signals:

public slots:
void run();


};



#endif // DATABASE_H
