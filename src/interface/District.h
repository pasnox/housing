/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : District.h
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
#ifndef DISTRICT_H
#define DISTRICT_H

#include <QSharedDataPointer>
#include <QList>
#include <QVariant>

class DistrictData;

class District
{
public:
    typedef QList<District> List;
    
    District( const QVariant& variant = QVariant() );
    District( const District& other );
    District( const QString& label, const QString& value, const QString& code, const QString& valuesup );
    virtual ~District();
    
    virtual District& operator=( const District& other );
    virtual bool operator==( const District& other ) const;
    virtual bool operator<( const District& other ) const;
    
    bool isNull() const;
    QString label() const;
    QString value() const;
    QString valuesup() const;
    QString code() const;
    
    QVariant toVariant() const;
    void fromVariant( const QVariant& variant );
    
    static QVariant listToVariant( const District::List& districts );
    static District::List variantToList( const QVariant& variant );

private:
    QSharedDataPointer<DistrictData> d;
};

#endif // DISTRICT_H
