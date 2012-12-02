/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : CityModel.h
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
#ifndef CITYMODEL_H
#define CITYMODEL_H

#include <QAbstractTableModel>

#include "City.h"

class CityModelPrivate;

class CityModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    enum CustomRoles {
        LabelRole = Qt::UserRole,
        ValueRole,
        CodeRole,
        // internal, do not use
        FirstRole = LabelRole,
        LastRole = CodeRole
    };
    
    CityModel( QObject* parent = 0 );
    virtual ~CityModel();
    
    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    
    void clear();
    
    void setCities( const City::List& cities );
    City::List cities() const;
    
    void addCity( const City& city );
    City city( const QModelIndex& index ) const;
    void removeCities( const QModelIndexList& indexes );
    
    void setCodeVisible( bool visible );
    bool isCodeVisible() const;

private:
    CityModelPrivate* d;
};

#endif // CITYMODEL_H
