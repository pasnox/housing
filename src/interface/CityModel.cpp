#include "CityModel.h"

#include <QDebug>

class CityModelPrivate {
public:
    City::List cities;
	bool codeVisible;

public:
	CityModelPrivate()
		: codeVisible( false )
	{
	}
};

CityModel::CityModel( QObject* parent )
    : QAbstractTableModel( parent ),
        d( new CityModelPrivate )
{
}

CityModel::~CityModel()
{
    delete d;
}

int CityModel::columnCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? CityModel::LastRole -CityModel::FirstRole : 0;
}

int CityModel::rowCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? d->cities.count() : 0;
}

QVariant CityModel::data( const QModelIndex& index, int role ) const
{
    if ( index.isValid() ) {
        const City& city = this->city( index );
        
        switch ( role ) {
            case Qt::DisplayRole:
            case Qt::EditRole: { 
                switch ( index.column()  ) {
                    case 0:
                        return d->codeVisible ? QString( "%1 (%2)" ).arg( city.label() ).arg( city.code() ) : city.label();
                    case 1:
                        return city.value();
                    case 2:
                        return city.code();
                }
                
                break;
            }
            
            case CityModel::LabelRole: {
                return city.label();
            }
            
            case CityModel::ValueRole: {
                return city.value();
            }
            
            case CityModel::CodeRole: {
                return city.code();
            }
        }
    }
    
    return QVariant();
}

QVariant CityModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole && section >= 0 && section < columnCount() ) {
        switch ( section +CityModel::FirstRole ) {
            case CityModel::LabelRole:
                return tr( "Label" );
            case CityModel::ValueRole:
                return tr( "Value" );
            case CityModel::CodeRole:
                return tr( "Code" );
            default:
                break;
        }
    }
    
    return QAbstractTableModel::headerData( section, orientation, role );
}

void CityModel::clear()
{
    const int count = d->cities.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginRemoveRows( QModelIndex(), 0, count -1 );
    d->cities.clear();
    endRemoveRows();
}

void CityModel::setCities( const City::List& cities )
{
    clear();
    
    const int count = cities.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginInsertRows( QModelIndex(), 0, count -1 );
    d->cities = cities;
    endInsertRows();
}

City::List CityModel::cities() const
{
    return d->cities;
}

void CityModel::addCity( const City& city )
{
	if ( d->cities.contains( city ) ) {
		return;
	}
	
	const int count = d->cities.count();
	
	beginInsertRows( QModelIndex(), count, count );
	d->cities << city;
	endInsertRows();
}

City CityModel::city( const QModelIndex& index ) const
{
    return d->cities.value( index.row() );
}

void CityModel::removeCities( const QModelIndexList& _indexes )
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
		
		d->cities.removeAt( index.row() );
	}
	
	changePersistentIndexList( oldIndexes, newIndexes );
	
	emit layoutChanged();
}

void CityModel::setCodeVisible( bool visible )
{
	d->codeVisible = visible;
	emit dataChanged( index( 0, 0 ), index( rowCount() -1, columnCount() -1 ) );
}

bool CityModel::isCodeVisible() const
{
	return d->codeVisible;
}
