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

void setUser(QString user);
QStringList getTickIntervalIndicator(int start,int end,QString name,QString rsi,QString cci,QString ma, QString so);
QString getTickIndicator(int index,QString name,QString rsi,QString cci,QString ma, QString so);
int removePopup(QString name,QString indicator,QString condition,QString threshold);
void addPopup(QString name,QString indicator,QString condition,QString threshold);
QStringList getallpopupscondition(QString stockname,QString conditionname);
void addIndicator(QString index,QString date,QString name,QString rsi,QString cci,QString ma,QString so);





//to be implemented




};



#endif // DATABASE_H
