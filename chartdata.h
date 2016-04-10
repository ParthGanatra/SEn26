#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QObject>
#include <QJsonObject>

class Chartdata : public QObject
{
    Q_OBJECT
    int Width, Height;

    public:
        explicit Chartdata(QObject *parent = 0);
        virtual ~Chartdata();

    public:
        Q_INVOKABLE QJsonObject getWH() const;
        Q_INVOKABLE void setWH(int width, int height);
};

#endif // CHARTDATA_H
