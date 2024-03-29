#include "all_popups_model.h"

All_Popups_Model::All_Popups_Model(QObject *parent) : QObject(parent)
{
}

All_Popups_Model::All_Popups_Model(const QString &stock,const QString &indicator,const QString &condition,const QString &threshold,QObject *parent) : QObject(parent), m_stock(stock), m_indicator(indicator), m_condition(condition), m_threshold(threshold)
{
}

QString All_Popups_Model::stock() const
{
    return m_stock;
}

void All_Popups_Model::setStock(const QString &stock)
{
    if (stock != m_stock)
    {
        m_stock = stock;
        emit stockChanged();
    }
}

QString All_Popups_Model::indicator() const
{
    return m_indicator;
}

void All_Popups_Model::setIndicator(const QString &indicator)
{
    if (indicator != m_indicator)
    {
        m_indicator = indicator;
        emit indicatorChanged();
    }
}

QString All_Popups_Model::condition() const
{
    return m_condition;
}

void All_Popups_Model::setCondition(const QString &condition)
{
    if (condition != m_condition)
    {
        m_condition = condition;
        emit conditionChanged();
    }
}

QString All_Popups_Model::threshold() const
{
    return m_threshold;
}

void All_Popups_Model::setThreshold(const QString &threshold)
{
    if (threshold != m_threshold)
    {
        m_threshold = threshold;
        emit thresholdChanged();
    }
}
