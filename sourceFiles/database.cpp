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
#include <QJsonDocument>
#include <QJsonObject>

#define 	MONGO_QUERY(x)   mongo::Query(BSON(x))

mongo::DBClientConnection c;

int dataloaded=-1;

Database::~Database()
{}


void Database::run() {

     QString temp2=username+".stock";

     mongo::BSONObjBuilder tokenbuild;
    mongo::BSONObj token;
     tokenbuild.append("index",-1);
     tokenbuild.append("date","token");
     tokenbuild.append("open","token");
     tokenbuild.append("high","token");
    tokenbuild.append("low","token");
    tokenbuild.append("close","token");
    tokenbuild.append("volume","token");
    tokenbuild.append("name","token");

    token=tokenbuild.obj();
     if((c.query(temp2.toStdString(),token)->more()))
      {
         dataloaded=1;
        return ;
       }
     else
     {
            c.insert(temp2.toStdString(),token);

     }

    for (int i=1;i<=stocklist.size();i++)
    {

        QFile file(QString::number(i));               // Enter your own path

        if (!file.open(QIODevice::ReadOnly)) {
               qDebug() << file.errorString();
               return;
        }
        int FieldCount=1;


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
                b.append("name",(stocklist.at(i-1).left(stocklist.at(i-1).length()-1)).toStdString());
                FieldCount++;

              //  qDebug() <<QString::fromStdString((stocklist.at(i-1).left(stocklist.at(i-1).length()-1)).toStdString());
                   mongo::BSONObj t=b.obj();


//                if(!(c.query(temp2.toStdString(),t)->more()))
                c.insert(temp2.toStdString(),t);

    //            i++;
               // b.done();



        }



    }


    dataloaded=1;

}




void Database::setUser(QString user)
{
    this->username=user;
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
    //if(dataloaded==-1)
       // return "";


    QString temp2=username+".stock";


    mongo::auto_ptr<mongo::DBClientCursor> cursor = c.query(temp2.toStdString(), MONGO_QUERY("index" << index<<"name"<<name.toStdString()));
    //std::auto_ptr<mongo::DBClientCursor> cursor = c.query("Stocks.APPLE", MONGO_QUERY("index" << index));
//   qDebug()<<QString::fromStdString(cursor->peekFirst().toString());


   // qDebug() << cursor->more();
    mongo::BSONObj temp=cursor->peekFirst();


    return QString::fromStdString(temp.jsonString());
}


QStringList Database ::getTickInterval(int start,int end,QString name)
{
    QStringList list;
    QString temp2=username+".stock";
    mongo::auto_ptr<mongo::DBClientCursor> cursor = c.query(temp2.toStdString(), MONGO_QUERY("name"<<name.toStdString()));
    mongo::BSONObj temp;
    QJsonObject temp1;
    int i=0;

    while(cursor->more()){

//        cursor->peek(temp,i);
        temp = cursor->next();
        QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(temp.jsonString()).toUtf8());
        temp1 = doc.object();
        if(end<temp1["index"].toInt())
            break;
        if(start<=temp1["index"].toInt()){
            list.append(QString::fromStdString(temp.jsonString()));
//            qDebug()<<list.at(i);
        }
        i++;
    }


//    if(dataloaded==-1)
//        return list;


//    for(int i=start;i<=end;i++)
//    {
//        list.append(getTick(i,name));
//     }

    return list;
}

int Database::removePopup(QString name,QString indicator,QString condition,QString threshold)
{

    QString temp=username+".popup";
    c.remove(temp.toStdString(),MONGO_QUERY("name" <<name.toStdString() << "indicator" <<indicator.toStdString()  <<  "condition" << condition.toStdString()<<"threshold"<<threshold.toStdString()));


}



QString Database:: getTickIndicator(int index,QString name,QString rsi,QString cci,QString ma, QString so)
{
    if(dataloaded==-1)
        return "";

    QString temp2=username+".indicator";




//    std::auto_ptr<mongo::DBClientCursor> cursor = c.query(temp2.toStdString(), MONGO_QUERY("index" << index << "name" << name.toStdString()));
    mongo::auto_ptr<mongo::DBClientCursor> cursor = c.query(temp2.toStdString(), MONGO_QUERY("index" << index << "name" << name.toStdString()<<"rsi"<<rsi.toStdString()<<"cci"<<cci.toStdString()<<"ma"<<ma.toStdString()<<"so"<<so.toStdString()));
    //std::auto_ptr<mongo::DBClientCursor> cursor = c.query("Stocks.APPLE", MONGO_QUERY("index" << index));
//    qDebug()<<QString::fromStdString(cursor->peekFirst().toString());

    mongo::BSONObj temp=cursor->peekFirst();


    return QString::fromStdString(temp.jsonString());
}


QStringList Database ::getTickIntervalIndicator(int start,int end,QString name,QString rsi,QString cci,QString ma, QString so)
{
    QStringList list;

    if(dataloaded==-1)
        return list;


    for(int i=start;i<=end;i++)
    {
        list.append(getTickIndicator(i,name,rsi,cci,ma,so));
     }

    return list;
}


void Database::addPopup(QString name,QString indicator,QString condition,QString threshold)
{
    mongo::BSONObjBuilder b;

    b.append("name",name.toStdString());
    b.append("indicator",indicator.toStdString());
    b.append("condition",condition.toStdString());
    b.append("threshold",threshold.toStdString());

    mongo::BSONObj t=b.obj();

    QString temp2=username+".popup";

    if(!c.query(temp2.toStdString(),t)->more())
    c.insert(temp2.toStdString(),t);

}

QStringList Database::getallpopupscondition(QString name,QString indicator)
{
       QString temp=username+".popup";

    mongo::auto_ptr<mongo::DBClientCursor> cursor = c.query(temp.toStdString(), MONGO_QUERY("name" << name.toStdString() << "indicator" << indicator.toStdString() ));
    //std::auto_ptr<mongo::DBClientCursor> cursor = c.query("Stocks.APPLE", MONGO_QUERY("index" << index));
//    qDebug()<<QString::fromStdString(cursor->peekFirst().toString());

    QStringList list;

    while(cursor->more())
    {
    list.append(QString::fromStdString(cursor->next().toString()));


    }

    return list;
}




void Database::addIndicator(QString index,QString date,QString name,QString rsi,QString cci,QString ma,QString so)
{
    mongo::BSONObjBuilder b;

    b.append("index",index.toStdString());
    b.append("date",date.toStdString());
    b.append("name",name.toStdString());
    b.append("rsi",rsi.toStdString());
    b.append("cci",cci.toStdString());
    b.append("ma",ma.toStdString());
    b.append("so",so.toStdString());

    mongo::BSONObj t=b.obj();

    QString temp2=username+".indicator";

   if(!c.query(temp2.toStdString(),t)->more())
    c.insert(temp2.toStdString(),t);



}



void Database::database_test()
{
/*    getTickInterval                test               status :Completed.
QStringList temp;

temp=this->getTickInterval(1,2,"A");

for(int i=0;i<temp.size();i++)
{
    qDebug() <<temp.at(i);
}
*/


 // test 2 and 3                   status : passed.

QStringList temp;
this->addPopup("A","RSI",">","25");
this->addPopup("A","RSI","<","15");
this->addPopup("A","RSI","<","7");
this->addPopup("A","so",">","25");
this->addPopup("A","MA",">","25");
this->addPopup("A","MA","<","12");

    temp=this->getallpopupscondition("A","RSI");

//for(int i=0;i<temp.size();i++)
//{
//     qDebug() <<temp.at(i);
//}


//int removePopup(QString name,QString indicator,QString condition,QString threshold);
this->removePopup("A","RSI",">","25");

//qDebug()<<"After Removing";

temp=this->getallpopupscondition("A","RSI");

//for(int i=0;i<temp.size();i++)
//{
// qDebug() <<temp.at(i);
//}

}
