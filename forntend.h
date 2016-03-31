#ifndef FORNTEND
#define FORNTEND

#include <QObject>
#include <QDebug>

class Forntent : public QObject
{
    Q_OBJECT

public:
    explicit Forntent(QObject *parent = 0);

signals:

public slots:
    int func();

};


#endif // FORNTEND

