#include "AnnouncementModel.h"

#include <QPixmapCache>
#include <QFont>
#include <QDebug>

#define AnnouncementModelColumnCount 5

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
		: emptyPixmap( QPixmap( 100, 100 ) ),
			canFetch( false ),
			page( -1 )
	{
        emptyPixmap.fill( Qt::transparent );
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
					const QString key = announcement.thumbnailInformations();
					QPixmap pixmap;
					
					if ( QPixmapCache::find( key, &pixmap ) ) {
						return pixmap;
					}
					else {
						if ( !key.isEmpty() ) {
							emit const_cast<AnnouncementModel*>( this ) ->requestImageDownload( key );
						}
					}
					
					return d->emptyPixmap;
				}
				
				break;
			}
			
            case Qt::DisplayRole:
            case Qt::EditRole: {
                switch ( index.column()  ) {
                    case 1:
                        return announcement.cityLocation();
                    case 2:
                        return announcement.zipLocation();
					case 3:
                        return announcement.pricePricing();
					case 4:
                        return announcement.titleInformations();
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
                return tr( "Thumbnail" );
            case 1:
                return tr( "City" );
            case 2:
                return tr( "Zip" );
            case 3:
                return tr( "Price" );
			case 4:
                return tr( "Title" );
        }
    }
    
    return QAbstractTableModel::headerData( section, orientation, role );
}

void AnnouncementModel::sort( int column, Qt::SortOrder order )
{
	qWarning( "%s: sort", Q_FUNC_INFO );
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
