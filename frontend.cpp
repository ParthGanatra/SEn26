#include "frontend.h"
#include <QJsonObject>
#include "../SMTP/SmtpMime"
#include "QTime"
#include "QtGlobal"
Frontend::Frontend(QObject *parent) :
    QObject(parent)
{
}


void Frontend::sendOTP(QString email,QString otp)
{

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);



        smtp.setUser("group26.sen@gmail.com");
        smtp.setPassword("Group26 SEn.");

        MimeMessage message;

        message.setSender(new EmailAddress("group26.sen@gmail.com", "GROUP 26"));
        message.addRecipient(new EmailAddress(email, "User"));
        message.setSubject("Group 26");

        MimeText text;




        text.setText("Your confirmaion key = "+otp+"");


        message.addPart(&text);

        smtp.connectToHost();
        smtp.login();
        smtp.sendMail(message);
        smtp.quit();


}

QString Frontend::generateOtp()
{

    QTime t;
    t.setHMS(5,7,3,2);
    int time=t.msecsTo(QTime::currentTime());

    if(time<0)
        time=-time;

    //qDebug()<<time;
    qsrand(time);

    QString str="";



    for(int i=0;i<6;i++)
    {
        str=str+QString::number(qrand()%10);

    }


    return str;
}
