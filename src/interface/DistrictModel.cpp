/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : DistrictModel.cpp
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
#include "DistrictModel.h"

#include <QDebug>

class DistrictModelPrivate {
public:
    District::List districts;
	bool codeVisible;

public:
	DistrictModelPrivate()
		: codeVisible( false )
	{
	}
};

DistrictModel::DistrictModel( QObject* parent )
    : QAbstractTableModel( parent ),
        d( new DistrictModelPrivate )
{
}

DistrictModel::~DistrictModel()
{
    delete d;
}

int DistrictModel::columnCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? DistrictModel::LastRole -DistrictModel::FirstRole : 0;
}

int DistrictModel::rowCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? d->districts.count() : 0;
}

QVariant DistrictModel::data( const QModelIndex& index, int role ) const
{
    if ( index.isValid() ) {
        const District& district = this->district( index );
        
        switch ( role ) {
            case Qt::DisplayRole:
            case Qt::EditRole: { 
                switch ( index.column()  ) {
                    case 0:
                        return d->codeVisible ? QString( "%1 (%2)" ).arg( district.label() ).arg( district.code() ) : district.label();
                    case 1:
                        return district.value();
                    case 2:
                        return district.code();
                }
                
                break;
            }
            
            case DistrictModel::LabelRole: {
                return district.label();
            }
            
            case DistrictModel::ValueRole: {
                return district.value();
            }
            
            case DistrictModel::CodeRole: {
                return district.code();
            }
        }
    }
    
    return QVariant();
}

QVariant DistrictModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole && section >= 0 && section < columnCount() ) {
        switch ( section +DistrictModel::FirstRole ) {
            case DistrictModel::LabelRole:
                return tr( "Label" );
            case DistrictModel::ValueRole:
                return tr( "Value" );
            case DistrictModel::CodeRole:
                return tr( "Code" );
            default:
                break;
        }
    }
    
    return QAbstractTableModel::headerData( section, orientation, role );
}

void DistrictModel::sort( int column, Qt::SortOrder order )
{
	Q_UNUSED( column );
	
	if ( rowCount() == 0 ) {
		return;
	}
	
	emit layoutAboutToBeChanged();
	
	const QModelIndexList oldIndexes = persistentIndexList();
	QModelIndexList newIndexes;
	
	QMap<int, District> oldMapping;
	QMap<District, int> newMapping;
	
	for ( int i = 0; i < d->districts.count(); i++ ) {
		oldMapping[ i ] = d->districts[ i ];
	}
	
	switch ( order ) {
		case Qt::AscendingOrder: {
			qSort( d->districts.begin(), d->districts.end() );
			break;
		}
		
		case Qt::DescendingOrder: {
			qSort( d->districts.begin(), d->districts.end(), qGreater<District>() );
			break;
		}
	}
	
	for ( int i = 0; i < d->districts.count(); i++ ) {
		newMapping[ d->districts[ i ] ] = i;
	}
	
	for ( int i = 0; i < oldIndexes.count(); i++ ) {
		const QModelIndex& index = oldIndexes[ i ];
		const District& district = oldMapping[ index.row() ];
		newIndexes << QAbstractTableModel::index( newMapping[ district ], index.column() );
	}
	
	changePersistentIndexList( oldIndexes, newIndexes );
	
	emit layoutChanged();
}

void DistrictModel::clear()
{
    const int count = d->districts.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginRemoveRows( QModelIndex(), 0, count -1 );
    d->districts.clear();
    endRemoveRows();
}

void DistrictModel::setDistricts( const District::List& districts )
{
    clear();
    
    const int count = districts.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginInsertRows( QModelIndex(), 0, count -1 );
    d->districts = districts;
	qSort( d->districts );
    endInsertRows();
}

District::List DistrictModel::districts() const
{
    return d->districts;
}

void DistrictModel::addDistrict( const District& district )
{
	if ( d->districts.contains( district ) ) {
		return;
	}
	
	const int count = d->districts.count();
	
	beginInsertRows( QModelIndex(), count, count );
	d->districts << district;
	endInsertRows();
	sort( 0 );
}

District DistrictModel::district( const QModelIndex& index ) const
{
    return d->districts.value( index.row() );
}

void DistrictModel::removeDistricts( const QModelIndexList& _indexes )
{
	if ( _indexes.isEmpty() ) {
		return;
	}
	
	QModelIndexList indexes = _indexes;
	
	qSort( indexes );
	
	emit layoutAboutToBeChanged();
	
	const QModelIndexList oldIndexes = persistentIndexList();
	QModelIndexList newIndexes;
	
	for ( int i = 0; i < oldIndexes.count(); i++ ) {
		newIndexes << QModelIndex();
	}
	
	for ( int i = indexes.count() -1; i >= 0; i-- ) {
		const QModelIndex& index = indexes[ i ];
		
		d->districts.removeAt( index.row() );
	}
	
	changePersistentIndexList( oldIndexes, newIndexes );
	
	emit layoutChanged();
}

void DistrictModel::setCodeVisible( bool visible )
{
	d->codeVisible = visible;
	emit dataChanged( index( 0, 0 ), index( rowCount() -1, columnCount() -1 ) );
}

bool DistrictModel::isCodeVisible() const
{
	return d->codeVisible;
}
