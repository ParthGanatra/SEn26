#ifndef ALL_POPUPS_MODEL_H
#define ALL_POPUPS_MODEL_H

#include <QObject>

class All_Popups_Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString stock READ stock WRITE setStock NOTIFY stockChanged)
    Q_PROPERTY(QString indicator READ indicator WRITE setIndicator NOTIFY indicatorChanged)
    Q_PROPERTY(QString condition READ condition WRITE setCondition NOTIFY conditionChanged)
    Q_PROPERTY(QString threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged)

public:
    All_Popups_Model(QObject *parent = 0);
    All_Popups_Model(const QString &stock,const QString &indicator,const QString &condition,const QString &threshold,QObject *parent = 0);
    QString stock() const;
    void setStock(const QString &stock);
    QString indicator() const;
    void setIndicator(const QString &indicator);
    QString condition() const;
    void setCondition(const QString &condition);
    QString threshold() const;
    void setThreshold(const QString &threshold);

signals:
    void stockChanged();
    void indicatorChanged();
    void conditionChanged();
    void thresholdChanged();

private:
    QString m_stock;
    QString m_indicator;
    QString m_condition;
    QString m_threshold;

public slots:
};

#endif // ALL_POPUPS_MODEL_H
