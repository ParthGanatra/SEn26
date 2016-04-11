#ifndef USERCONFIG_H
#define USERCONFIG_H

#include<QString>
#include<QObject>

class UserConfig : public QObject
{
    Q_OBJECT

public:
    QString firstname;
    QString lastname;
    QString email;
    QString password;

    explicit UserConfig(QObject *parent = 0);

public slots:
    void saveConfig();


};




#endif // USERCONFIG_H
