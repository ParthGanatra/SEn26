#include<helper.h>
#include<QCryptographicHash>
#include<QByteArray>
#include<QString>
#include<QFile>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonObject>
#include<QTextStream>

Helper::Helper(QObject *parent) :
    QObject(parent)
{
}

QString Helper::compute_hash(std::string p)
{
    QByteArray qb = QCryptographicHash::hash(QByteArray::fromStdString(p),QCryptographicHash::Sha3_512);
    QString hash = qb.toHex();
    return hash;
}

bool Helper::verify_user_password(QString u, QString p)
{
    qDebug() << "verifying password" << endl;
    QString stored_hash;
    QFile file;
    file.setFileName("Users/" + u + ".conf");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "No such user";
        return false;
    }
    QTextStream in(&file);
    stored_hash = in.readLine();
    stored_hash = in.readLine();
    stored_hash = in.readLine();
    stored_hash = in.readLine();

    QString computated_hash = Helper::compute_hash(p.toStdString());
    qDebug() << computated_hash << endl;
    qDebug() << stored_hash << endl;
    bool result = !QString::compare(computated_hash,stored_hash);
    qDebug() << result << endl;
    return result;
}
