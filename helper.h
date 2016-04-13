#ifndef HELPER_H
#define HELPER_H

#include<QObject>
#include<QCryptographicHash>
#include<QByteArray>
#include<QString>
#include<QFile>
#include<QDebug>

#include "backend.h"
#include "database.h"

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = 0);

public slots:
    QString compute_hash(std::string p);
    bool verify_user_password(QString u, QString p);
    int check_valid_detail(QString f, QString l, QString e,QString p,QString vp);
    bool isValidEmailAddress(std::string);
    bool isNumber(const char Character);
    bool isCharacter(const char Character);
    QString get_user_email(QString u);
    void change_password(QString u, QString p);
    QString get_user_lastname(QString u);
    void change_details(QString old_user, QString nu, QString l, QString email);
};


#endif // HELPER_H
