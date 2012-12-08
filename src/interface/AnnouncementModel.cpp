/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : AnnouncementModel.cpp
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
#include "AnnouncementModel.h"

#include <QPixmapCache>
#include <QFont>
#include <QDebug>

#define AnnouncementModelColumnCount 7

class AnnouncementModelPrivate {
public:
    Announcement::List announcements;
	QSet<int> ignoredIdSet;
	QSet<int> bookmarkedIdSet;
	QPixmap emptyPixmap;
	bool canFetch;
	int page;

public:
	AnnouncementModelPrivate()
		: emptyPixmap( QPixmap( ":/picture-not-available.png" ) ),
			canFetch( false ),
			page( -1 )
	{
	}
};

AnnouncementModel::AnnouncementModel( QObject* parent )
    : QAbstractTableModel( parent ),
        d( new AnnouncementModelPrivate )
{
}

AnnouncementModel::~AnnouncementModel()
{
    delete d;
}

int AnnouncementModel::columnCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? AnnouncementModelColumnCount : 0;
}

int AnnouncementModel::rowCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? d->announcements.count() : 0;
}

QVariant AnnouncementModel::data( const QModelIndex& index, int role ) const
{
    if ( index.isValid() ) {
        const Announcement announcement = this->announcement( index );
        
        switch ( role ) {
			case Qt::DecorationRole: {
				if ( index.column() == 0 ) {
					return data( index, AnnouncementModel::ThumbnailRole );
				}
				
				break;
			}
			
            case Qt::DisplayRole:
            case Qt::EditRole: {
				switch ( index.column() ) {
					case 0:
						return announcement.cityLocation();
					case 1:
						return announcement.zipLocation();
					case 2:
						return announcement.pricePricing();
					case 3:
						return announcement.roomsNumbers();
					case 4:
						return announcement.bedroomsNumbers();
					case 5:
						return announcement.houseSurfaceDetails();
					case 6:
						return 0;//announcement.groundSurfaceDetails();
				}
                
                break;
            }
			
			case Qt::ToolTipRole:
            case Qt::WhatsThisRole: {
				QStringList strings;
				QStringList extraInformations;
				
				if ( !announcement.labelInformations().isEmpty() ) {
					extraInformations << announcement.labelInformations();
				}
				
				if ( !announcement.nearLocation().isEmpty() ) {
					extraInformations << announcement.nearLocation();
				}
				
				strings << QString( "%1 (%2) - %3 - %4 (%5)" )
					.arg( announcement.titleInformations() )
					.arg( extraInformations.join( ", " ) )
					.arg( announcement.countryLocation() )
					.arg( announcement.cityLocation() )
					.arg( announcement.zipLocation() )
				;
				
				strings << QString( "%1 %2" )
					.arg( announcement.pricePricing() )
					.arg( announcement.currencyPricing() )
				;
				
				if ( !announcement.mentionPricing().isEmpty() ) {
					strings.last().append( QString( " (%1)" ).arg( announcement.mentionPricing() ) );
				}
				
				if ( !announcement.descriptionInformations().isEmpty() ) {
					strings << QString::null;
					strings << announcement.descriptionInformations();
				}
				
				strings << QString::null;
				strings << QString( "%1 / %2" )
					.arg( announcement.created().toString( Qt::SystemLocaleLongDate ) )
					.arg( announcement.updated().toString( Qt::SystemLocaleLongDate ) )
				;
				
                return strings.join( "\n" ).replace( "\n", "<br />" );
            }
			
			case AnnouncementModel::IdRole: {
				return announcement.id();
			}
			
			case AnnouncementModel::ThumbnailRole: {
				const QString key = announcement.thumbnailInformations();
				QPixmap pixmap;
				
				if ( QPixmapCache::find( key, &pixmap ) ) {
					return pixmap;
				}
				else {
					if ( !key.isEmpty() ) {
						emit const_cast<AnnouncementModel*>( this )->requestImageDownload( key );
					}
				}
				
				return d->emptyPixmap;
			}
			
			case AnnouncementModel::UrlRole: {
				return announcement.url();
			}
			
			case AnnouncementModel::IgnoredRole: {
				return d->ignoredIdSet.contains( announcement.id() );
			}
			
			case AnnouncementModel::BookmarkedRole: {
				return d->bookmarkedIdSet.contains( announcement.id() );
			}
			
			case AnnouncementModel::AnnouncementRole: {
				return announcement;
			}
        }
    }
    
    return QVariant();
}

QVariant AnnouncementModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole && section >= 0 && section < columnCount() ) {
        switch ( section ) {
            case 0:
                return tr( "City" );
            case 1:
                return tr( "Zip" );
            case 2:
                return tr( "Price" );
			case 3:
                return tr( "Rooms" );
			case 4:
                return tr( "Bedrooms" );
			case 5:
                return tr( "Surface" );
			case 6:
                return tr( "Ground" );
        }
    }
    
    return QAbstractTableModel::headerData( section, orientation, role );
}

bool AnnouncementModel::canFetchMore( const QModelIndex& parent ) const
{
	return parent == QModelIndex() ? d->canFetch : false;
}

void AnnouncementModel::fetchMore( const QModelIndex& parent )
{
	if ( parent == QModelIndex() && d->canFetch ) {
		d->canFetch = false;
		emit requestFetchMore();
	}
}

void AnnouncementModel::clear()
{
    const int count = d->announcements.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginRemoveRows( QModelIndex(), 0, count -1 );
    d->announcements.clear();
    endRemoveRows();
}

void AnnouncementModel::addAnnouncements( const Announcement::List& announcements )
{
	const int rcount = rowCount();
	const int count = announcements.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginInsertRows( QModelIndex(), rcount, rcount +count -1 );
    d->announcements << announcements;
    endInsertRows();
}

void AnnouncementModel::addAnnouncement( const Announcement& announcement )
{
	addAnnouncements( Announcement::List() << announcement );
}

void AnnouncementModel::setAnnouncements( const Announcement::List& announcements )
{
    clear();
	addAnnouncements( announcements );
}

void AnnouncementModel::removeAnnouncements( const QModelIndexList& _indexes )
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
		
		d->announcements.removeAt( index.row() );
	}
	
	changePersistentIndexList( oldIndexes, newIndexes );
	
	emit layoutChanged();
}

void AnnouncementModel::removeAnnouncement( const QModelIndex& index )
{
	removeAnnouncements( QModelIndexList() << index );
}

Announcement::List AnnouncementModel::announcements() const
{
    return d->announcements;
}

Announcement AnnouncementModel::announcement( const QModelIndex& index ) const
{
    return d->announcements.value( index.row() );
}

void AnnouncementModel::setCanFetchMore( bool can )
{
	d->canFetch = can;
}

void AnnouncementModel::setCurrentPage( int page )
{
	d->page = page;
}

int AnnouncementModel::currentPage() const
{
	return d->page;
}

void AnnouncementModel::setIgnoredIdSet( const QSet<int> ids )
{
	d->ignoredIdSet = ids;
	update();
}

QSet<int> AnnouncementModel::ignoredIdSet() const
{
	return d->ignoredIdSet;
}

void AnnouncementModel::setBookmarkedIdSet( const QSet<int> ids )
{
	d->bookmarkedIdSet = ids;
	update();
}

QSet<int> AnnouncementModel::bookmarkedIdSet() const
{
	return d->bookmarkedIdSet;
}

void AnnouncementModel::update()
{
	if ( rowCount() == 0 ) {
		return;
	}
	
	emit dataChanged( index( 0, 0 ), index( rowCount() -1, columnCount() -1 ) );
}
