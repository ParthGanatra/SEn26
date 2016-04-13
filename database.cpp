#include "database.h"

#include <mongo/client/dbclient.h>
#include <mongo/bson/bsonobjbuilder.h>
#include <mongo/bson/bsonobj.h>
#include <mongo/client/dbclientcursor.h>
#include <QFile>
#include <QByteArray>
#include <QStringList>
#include <QList>
#include <mongo/client/dbclientinterface.h>
#include <QStringList>

#define 	MONGO_QUERY(x)   mongo::Query(BSON(x))

mongo::DBClientConnection c;

int dataloaded=-1;




void Database::setUser(QString user)
{
    this->username=user;
}




int Database :: storePopup(QString json)
{
mongo::BSONObj temp= mongo::fromjson(json.toStdString());

c.insert("stock.popup",temp);


}

Database::Database(QObject *parent) :
    QObject(parent)
{
    this->username=username;
    c.connect("localhost");
}

int tickcount=1;

QString Database:: getTick(int index,QString name)
{
    if(dataloaded==-1)
        return "";

    QString temp2=username+".stock";



    mongo::auto_ptr<mongo::DBClientCursor> cursor = c.query(temp2.toStdString(), MONGO_QUERY("index" << index << "name" << name.toStdString()));
    //std::auto_ptr<mongo::DBClientCursor> cursor = c.query("Stocks.APPLE", MONGO_QUERY("index" << index));
    qDebug()<<QString::fromStdString(cursor->peekFirst().toString());

    mongo::BSONObj temp=cursor->peekFirst();


    return QString::fromStdString(temp.jsonString());
}


QStringList Database ::getTickInterval(int start,int end,QString name)
{
    QStringList list;

    if(dataloaded==-1)
        return list;


    for(int i=start;i<=end;i++)
    {
        list.append(getTick(i,name));
     }

    return list;
}



int FieldCount=1;

void Database::run() {




    QFile file("Data.csv");               // Enter your own path

    if (!file.open(QIODevice::ReadOnly)) {
           qDebug() << file.errorString();
           return;
    }

    while (!file.atEnd()) {
           QString line = file.readLine();


           mongo::BSONObjBuilder b;

           //qDebug() << line.split(',').value(1);

            b.append("index",FieldCount);
            b.append("date",line.split(',').value(0).toStdString());
            b.append("open",line.split(',').value(1).toStdString());
            b.append("high",line.split(',').value(2).toStdString());
            b.append("low",line.split(',').value(3).toStdString());
            b.append("close",line.split(',').value(4).toStdString());
            b.append("volume",line.split(',').value(5).toStdString());
            b.append("name","APPLE");
            FieldCount++;
          //  qDebug()<<QString::fromStdString(b.obj().toString());

            QString temp2=username+".stock";
            c.insert(temp2.toStdString().c_str(),b.obj());

//            i++;
           // b.done();

    }

    dataloaded=1;

}




int Database::removePopup(QString name,QString indicator,QString condition,QString threshold)
{

    QString temp=username+".popup";
    c.remove(temp.toStdString(),MONGO_QUERY("name" <<name.toStdString() << "indicator" <<indicator.toStdString()  <<  "condition" << condition.toStdString()<<"threshold"<<threshold.toStdString()));


}





