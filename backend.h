#ifndef BACKEND
#define BACKEND

#include <QObject>
#include <QDebug>
#include <QJsonArray>

class Backend : public QObject
{
    Q_OBJECT

    QJsonArray Popup_data;



public:
    explicit Backend(QObject *parent = 0);

signals:

public slots:
    void add_popup_data();
    void remove_Popup_data(int index);
    QJsonArray get_Popup_data();
    int get_Popup_size();

};


#endif // BACKEND

