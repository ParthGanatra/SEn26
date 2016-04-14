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
    if(u.isNull() || p.isNull())
        return false;
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
    file.close();
    return result;
}

int Helper::check_valid_detail(QString f, QString l, QString e, QString p, QString vp)
{
    qDebug() << "Checking for valid detail" << endl;

    if(f.isEmpty())
        return 1;

    if(l.isEmpty())
        return 2;

    if(!isValidEmailAddress(e.toStdString()))
        return 3;

    if(p.length()<8)
        return 4;

    if(QString::compare(p,vp))
        return 5;
    return 0;
}

bool Helper::isCharacter(const char Character)
{
    return ( (Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z'));
    //Checks if a Character is a Valid A-Z, a-z Character, based on the ascii value
}

bool Helper::isNumber(const char Character)
{
    return ( Character >= '0' && Character <= '9');
    //Checks if a Character is a Valid 0-9 Number, based on the ascii value
}

bool Helper::isValidEmailAddress(std::string email)
{
    const char* EmailAddress = email.c_str();
    if(!EmailAddress) // If cannot read the Email Address...
        return 0;
    if(!isCharacter(EmailAddress[0])) // If the First character is not A-Z, a-z
        return 0;
    int AtOffset = -1;
    int DotOffset = -1;
    unsigned int Length = strlen(EmailAddress); // Length = StringLength (strlen) of EmailAddress
    for(unsigned int i = 0; i < Length; i++)
    {
        if(EmailAddress[i] == '@') // If one of the characters is @, store it's position in AtOffset
            AtOffset = (int)i;
        else if(EmailAddress[i] == '.') // Same, but with the dot
            DotOffset = (int)i;
    }
    if(AtOffset == -1 || DotOffset == -1) // If cannot find a Dot or a @
        return 0;
    if(AtOffset > DotOffset) // If the @ is after the Dot
        return 0;
    return !(DotOffset >= ((int)Length-1)); //Chech there is some other letters after the Dot
}

QString Helper::get_user_lastname(QString u)
{
    qDebug() << "Lastname" + u + "\n";
    if(u.isNull())
        return "null";
    QString temp = "Users/" + u + ".conf";
    std::string user = temp.toStdString();
    QFile file;
    file.setFileName(temp);
    if(file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString lastname;
            lastname = in.readLine();
            lastname = in.readLine();
            file.close();
            qDebug() << lastname;
            return lastname;
        }
        return "null";
    }
}

QString Helper::get_user_email(QString u)
{
    qDebug() << "Email" + u + "\n";
    if(u.isNull())
        return "null";

    QFile file;
    file.setFileName("Users/" + u + ".conf");
    if(file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString email;
            email = in.readLine();
            email = in.readLine();
            email = in.readLine();
            file.close();
            qDebug() << email;
            return email;
        }
        return "null";
    }
    else{
        return "null";
    }
}

void Helper::change_password(QString u, QString p)
{
    QFile file;
    file.setFileName("Users/" + u + ".conf");
    QString fn,ln,em;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QTextStream out(&file);

        fn = in.readLine();
        ln = in.readLine();
        em = in.readLine();
        file.close();
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << fn + "\n";
        out << ln + "\n";
        out << em + "\n";
        out << compute_hash(p.toStdString()) <<"\n";
        file.close();
        qDebug() << "Password Succesfully Changed";
    }

}

void Helper::change_details(QString old_user, QString nu, QString l, QString email)
{
    QFile file;
    file.setFileName("Users/" + old_user + ".conf");
    QString old_pass;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        old_pass = in.readLine();
        old_pass = in.readLine();
        old_pass = in.readLine();
        old_pass = in.readLine();
    }
    file.remove();
    file.close();
    file.setFileName("Users/" + nu + ".conf");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << nu + "\n";
        out << l + "\n";
        out << email + "\n";
        out << old_pass <<"\n";
        file.close();
        qDebug() << "Password Succesfully Changed";
    }
}
