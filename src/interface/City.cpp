#include "City.h"

#include <QSharedData>
#include <QString>

class CityData : public QSharedData {
public:
    QString label;
    QString value;
    QString code;
    
public:
    CityData() {
    }
    
    CityData( const CityData& other )
        : QSharedData( other ),
            label( other.label ),
            value( other.value ),
            code( other.code )
    {
    }
    
    ~CityData() {
    }
};

City::City( const QVariant& variant )
    : d( new CityData )
{
    if ( !variant.isNull() ) {
        fromVariant( variant );
    }
}

City::City( const City& other )
    : d( other.d )
{
}

City::City( const QString& label, const QString& value, const QString& code )
    : d( new CityData )
{
    d->label = label;
    d->value = value;
    d->code = code;
}

City::~City()
{
}

bool City::operator==( const City& other ) const
{
    return d->value == other.d->value;
}

bool City::isNull() const
{
    return d->label.isEmpty() &&
        d->value.isEmpty() &&
        d->code.isEmpty()
    ;
}

QString City::label() const
{
    return d->label;
}

QString City::value() const
{
    return d->value;
}

QString City::code() const
{
    return d->code;
}

QVariant City::toVariant() const
{
    QVariantMap map;
    map[ "label" ] = d->label;
    map[ "value" ] = d->value;
    map[ "code" ] = d->code;
    return map;
}

void City::fromVariant( const QVariant& variant )
{
    if ( !variant.type() == QVariant::Map ) {
        return;
    }
    
    const QVariantMap map = variant.toMap();
    d->label = map.value( "label" ).toString();
    d->value = map.value( "value" ).toString();
    d->code = map.value( "code" ).toString();
}

QVariant City::listToVariant( const City::List& cities )
{
    QVariantList list;
    
    foreach ( const City& city, cities ) {
        list << city.toVariant();
    }
    
    return list;
}

City::List City::variantToList( const QVariant& variant )
{
    City::List list;
    
    if ( variant.type() == QVariant::List ) {
        const QVariantList cities = variant.toList();
        
        foreach ( const QVariant& city, cities ) {
            list << City( city );
        }
    }
    
    return list;
}
