#include "userconfig.h"

#include<QFile>
#include<QTextStream>

UserConfig::UserConfig(QObject *parent) :
    QObject(parent)
{

}



void UserConfig ::saveConfig()
{
    QFile file("/home/harshil/Desktop/SEN/user.conf");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);
    out << firstname <<"\n";
    out << lastname <<"\n";
    out << email <<"\n";
    out << password <<"\n";

    file.close();
}
