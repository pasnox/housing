/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : AbstractDistrictQuery.h
** Date      : 2015-09-05T23:26:14
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
#ifndef ABSTRACTDISTRICTQUERY_H
#define ABSTRACTDISTRICTQUERY_H

#include <QObject>

#include "District.h"

class AbstractDistrictQuery : public QObject
{
    Q_OBJECT
    
public:
    AbstractDistrictQuery( QObject* parent = 0 );
    virtual ~AbstractDistrictQuery();

    virtual void setMinimumSearchLength( int length ) = 0;
    virtual int minimumSearchLength() const = 0;

public slots: 
    virtual void search( const QString& text ) = 0;

signals:
    void districtsReceived( const District::List& districts );
    void error( const QString& error );
};

#endif // ABSTRACTDISTRICTQUERY_H
