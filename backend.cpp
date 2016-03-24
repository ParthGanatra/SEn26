#include "backend.h"
#include <QJsonObject>

Backend::Backend(QObject *parent) :
    QObject(parent)
{
}

void Backend::add_popup_data()
{
    for(int i=0;i<15;i++){
        QJsonObject temp1;
        temp1["stock"] = "STOCK1";
        temp1["indicator"] = "INDICATOR1";
        temp1["condition"] = "CONDITION1";
        if(i==2){
            temp1["stock"] = "STOCK112";
            temp1["indicator"] = "INDICATOR1123";
            temp1["condition"] = "CONDITION1132";
        }
        Popup_data.append(temp1);
    }
}

void Backend::remove_Popup_data(int index)
{
    Popup_data.removeAt(index);
    qDebug() << index;
}

int Backend::get_Popup_size()
{
    return Popup_data.size();
}

QJsonArray Backend::get_Popup_data()
{
    return Popup_data;
}

