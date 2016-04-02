#include "frontend.h"
#include <QJsonObject>
#include "../SMTP/SmtpMime"
Frontend::Frontend(QObject *parent) :
    QObject(parent)
{
}


void Frontend::sendOTP(QString email)
{

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);



        smtp.setUser("group26.sen@gmail.com");
        smtp.setPassword("Group26 SEn.");

        MimeMessage message;

        message.setSender(new EmailAddress("group26.sen@gmail.com", "GROUP 26"));
        message.addRecipient(new EmailAddress("basahu@leeching.net", "harshil"));
        message.setSubject("Group 26");

        MimeText text;

        text.setText("test confirmaion key = 123456789.");


        message.addPart(&text);

        smtp.connectToHost();
        smtp.login();
        smtp.sendMail(message);
        smtp.quit();


}
