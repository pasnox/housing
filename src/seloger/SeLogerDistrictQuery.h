/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : SeLogerDistrictQuery.h
** Date      : 2015-09-05T23:32:14
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
#ifndef SELOGERDISTRICTQUERY_H
#define SELOGERDISTRICTQUERY_H

#include "interface/AbstractDistrictQuery.h"

class SeLogerDistrictQueryPrivate;

class SeLogerDistrictQuery : public AbstractDistrictQuery
{
    Q_OBJECT
    
public:
    SeLogerDistrictQuery( QObject* parent = 0 );
    virtual ~SeLogerDistrictQuery();

    virtual void setMinimumSearchLength( int length );
    virtual int minimumSearchLength() const;

public slots: 
    virtual void search( const QString& text );

private:
    SeLogerDistrictQueryPrivate* d;
};

#endif // SELOGERDISTRICTQUERY_H
