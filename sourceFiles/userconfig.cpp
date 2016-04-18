#include "userconfig.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QString>
#include<QObject>
#include<QDir>
#include "helper.h"

UserConfig::UserConfig(QObject *parent) :
    QObject(parent)
{

}

void UserConfig ::saveConfig(QString f, QString l, QString e, QString p)
{
    qDebug() << "saving file";
    if(!QDir("Users").exists())
        QDir().mkdir("Users");

    QFile file("Users/" + f +".conf");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Error coundn't write to file";
        return;
    }
    Helper userconfig_helper;
    QTextStream out(&file);
    out << f <<"\n";
    out << l <<"\n";
    out << e <<"\n";
    //    std::string utf8_text = p.toUtf8().constData()
    out << userconfig_helper.compute_hash(p.toStdString()) <<"\n";
    qDebug() << "saved file";
    file.close();
}

