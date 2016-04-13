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
    virtual ~Database();

    QString username;

signals:

public slots:

void run();
QString getTick(int index,QString name);
QStringList getTickInterval(int start,int end,QString name);
int storePopup(QString jsonString);

void setUser(QString user);
//to be implemented
int removePopup(QString name,QString indicator,QString condition,QString threshold);





};



#endif // DATABASE_H
