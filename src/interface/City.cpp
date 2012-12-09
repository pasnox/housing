/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : City.cpp
** Date      : 2012-12-02T21:57:14
** License   : GPL3
** Home Page : https://github.com/pasnox/housing
** Comment   : An application to search for rent / purchase of appartment / house.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This package is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
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

City& City::operator=( const City& other )
{
    if ( this != &other ) {
        d = other.d;
    }
    
    return *this;
}

bool City::operator==( const City& other ) const
{
    return d->value == other.d->value;
}

bool City::operator<( const City& other ) const
{
    return d->label.compare( other.d->label ) < 0;
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
