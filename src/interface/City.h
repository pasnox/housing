/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : City.h
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
