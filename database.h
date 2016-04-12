#ifndef DATABASE_H
#define DATABASE_H



#include <QObject>
#include <QDebug>
#include <QStringList>
//#include <mongo/bson/bsonobjbuilder.h>


class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = 0);

signals:

public slots:
void run();
QString getTick(int index);
QStringList getTickInterval(int start,int end);

int storePopup(QString json);

};



#endif // DATABASE_H
