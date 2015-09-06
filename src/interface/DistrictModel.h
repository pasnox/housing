/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : DistrictModel.h
** Date      : 2015-09-06T00:07:14
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
#ifndef DISTRICTMODEL_H
#define DISTRICTMODEL_H

#include <QAbstractTableModel>

#include "District.h"

class DistrictModelPrivate;

class DistrictModel : public QAbstractTableModel
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
    
    DistrictModel( QObject* parent = 0 );
    virtual ~DistrictModel();
    
    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    virtual void sort( int column, Qt::SortOrder order = Qt::AscendingOrder );
    
    void clear();
    
    void setDistricts( const District::List& districts );
    District::List districts() const;
    
    void addDistrict( const District& district );
    District district( const QModelIndex& index ) const;
    void removeDistricts( const QModelIndexList& indexes );
    
    void setCodeVisible( bool visible );
    bool isCodeVisible() const;

private:
    DistrictModelPrivate* d;
};

#endif // DISTRICTMODEL_H
