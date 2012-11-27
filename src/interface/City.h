#ifndef CITY_H
#define CITY_H

#include <QSharedDataPointer>
#include <QList>
#include <QVariant>

class CityData;

class City
{
public:
    typedef QList<City> List;
    
    City( const QVariant& variant = QVariant() );
    City( const City& other );
    City( const QString& label, const QString& value, const QString& code );
    virtual ~City();
    
    virtual City& operator=( const City& other );
    virtual bool operator==( const City& other ) const;
    
    bool isNull() const;
    QString label() const;
    QString value() const;
    QString code() const;
    
    QVariant toVariant() const;
    void fromVariant( const QVariant& variant );
    
    static QVariant listToVariant( const City::List& cities );
    static City::List variantToList( const QVariant& variant );

private:
    QSharedDataPointer<CityData> d;
};

#endif // CITY_H
