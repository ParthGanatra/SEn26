#ifndef FRONTEND
#define FRONTEND

#include <QObject>
#include <QDebug>

class Frontend : public QObject
{
    Q_OBJECT

public:
    explicit Frontend(QObject *parent = 0);

signals:

public slots:
    void sendOTP(QString email,QString otp);
    QString generateOtp();
    int SaveConfiguration();
};


#endif // FORNTEND

