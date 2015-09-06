/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : District.cpp
** Date      : 2015-09-05T23:44:14
** License   : GPL3
** Home Page : https://github.com/don-vip/housing
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
#include "District.h"

#include <QSharedData>
#include <QString>

class DistrictData : public QSharedData {
public:
    QString label;
    QString value;
    QString valuesup;
    QString code;
    
public:
    DistrictData() {
    }
    
    DistrictData( const DistrictData& other )
        : QSharedData( other ),
            label( other.label ),
            value( other.value ),
            valuesup( other.valuesup ),
            code( other.code )
    {
    }
    
    ~DistrictData() {
    }
};

District::District( const QVariant& variant )
    : d( new DistrictData )
{
    if ( !variant.isNull() ) {
        fromVariant( variant );
    }
}

District::District( const District& other )
    : d( other.d )
{
}

District::District( const QString& label, const QString& value, const QString& code, const QString& valuesup )
    : d( new DistrictData )
{
    d->label = label;
    d->value = value;
    d->valuesup = valuesup;
    d->code = code;
}

District::~District()
{
}

District& District::operator=( const District& other )
{
    if ( this != &other ) {
        d = other.d;
    }
    
    return *this;
}

bool District::operator==( const District& other ) const
{
    return d->value == other.d->value && d->valuesup == other.d->valuesup;
}

bool District::operator<( const District& other ) const
{
    return d->label.compare( other.d->label ) < 0;
}

bool District::isNull() const
{
    return d->label.isEmpty() &&
        d->value.isEmpty() &&
        d->valuesup.isEmpty() &&
        d->code.isEmpty()
    ;
}

QString District::label() const
{
    return d->label;
}

QString District::value() const
{
    return d->value;
}

QString District::valuesup() const
{
    return d->valuesup;
}

QString District::code() const
{
    return d->code;
}

QVariant District::toVariant() const
{
    QVariantMap map;
    map[ "label" ] = d->label;
    map[ "value" ] = d->value;
    map[ "valuesup" ] = d->valuesup;
    map[ "code" ] = d->code;
    return map;
}

void District::fromVariant( const QVariant& variant )
{
    if ( !variant.type() == QVariant::Map ) {
        return;
    }
    
    const QVariantMap map = variant.toMap();
    d->label = map.value( "label" ).toString();
    d->value = map.value( "value" ).toString();
    d->valuesup = map.value( "valuesup" ).toString();
    d->code = map.value( "code" ).toString();
}

QVariant District::listToVariant( const District::List& districts )
{
    QVariantList list;
    
    foreach ( const District& district, districts ) {
        list << district.toVariant();
    }
    
    return list;
}

District::List District::variantToList( const QVariant& variant )
{
    District::List list;
    
    if ( variant.type() == QVariant::List ) {
        const QVariantList districts = variant.toList();
        
        foreach ( const QVariant& district, districts ) {
            list << District( district );
        }
    }
    
    return list;
}
