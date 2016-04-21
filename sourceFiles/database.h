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
    QStringList stocklist;

signals:

public slots:

    /*   Important Note
  *   While passing arguments in the below functions always append stock name with \n see database_test() for further refernece.
  *
 */
    void run();
    QString getTick(int index,QString name);
    QStringList getTickInterval(int start,int end,QString name);

    void setUser(QString user);
    QStringList getTickIntervalIndicator(int start,int end,QString name);
    QString getTickIndicator(int index,QString name,QString rsi,QString cci,QString ma, QString so);
    int removePopup(QString name,QString indicator,QString condition,QString threshold);
    void addPopup(QString name,QString indicator,QString condition,QString threshold);
    QStringList getallpopupscondition(QString stockname,QString indicator);
    void addIndicator(QString index,QString date,QString name,QString rsi,QString cci,QString ma,QString so);
    QStringList getIndex(int index);
    //for testing purposes
    void database_test();

};



#endif // DATABASE_H
