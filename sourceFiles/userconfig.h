#ifndef USERCONFIG_H
#define USERCONFIG_H

#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QString>
#include<QObject>
#include<QDir>


extern QString firstname;
extern QString lastname;
extern QString email;
extern QString password;

class UserConfig : public QObject
{
    Q_OBJECT

public:
    explicit UserConfig(QObject *parent = 0);

public slots:
    void saveConfig(QString f, QString l, QString e, QString p);
};

#endif // USERCONFIG_H
