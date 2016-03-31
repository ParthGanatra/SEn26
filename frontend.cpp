#include "forntend.h"
#include <QJsonObject>

Forntent::Forntent(QObject *parent) :
    QObject(parent)
{
}

int Forntent::func()
{
    qDebug() << "In C++ function";
    return 1;
}

