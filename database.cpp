#include "database.h"




Database::Database(QObject *parent) :
    QObject(parent)
{
}





void Database::run() {
  mongo::DBClientConnection c;
  c.connect("localhost");
}



