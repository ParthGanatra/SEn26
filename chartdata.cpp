#include "chartdata.h"

#include <QtCore/QDebug>
#include <QJsonObject>

Chartdata::Chartdata(QObject *parent)
    : QObject(parent)
{
}

Chartdata::~Chartdata()
{}

QJsonObject Chartdata::getWH() const
{
    qDebug()<<"asdasd";
    QJsonObject temp;
    temp["width"] = Width;
    temp["height"] = Height;
    return temp;
}

void Chartdata::setWH(int width, int height){
    Width = width;
    Height = height;
}
