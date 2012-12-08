/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : FeedbackModel.cpp
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
#include "FeedbackModel.h"

#include <QDateTime>
#include <QDebug>

#define FeedbackModelColumnCount 2

class FeedbackModelPrivate {
public:
    Feedback::List feedbacks;

public:
	FeedbackModelPrivate() {
	}
	
	static bool lessThanMessage( const Feedback& left, const Feedback& right ) {
		return left.message().compare( right.message(), Qt::CaseInsensitive ) < 0;
	}
	
	static bool greaterThanMessage( const Feedback& left, const Feedback& right ) {
		return left.message().compare( right.message(), Qt::CaseInsensitive ) > 0;
	}
};

FeedbackModel::FeedbackModel( QObject* parent )
    : QAbstractTableModel( parent ),
        d( new FeedbackModelPrivate )
{
}

FeedbackModel::~FeedbackModel()
{
    delete d;
}

int FeedbackModel::columnCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? FeedbackModelColumnCount : 0;
}

int FeedbackModel::rowCount( const QModelIndex& parent ) const
{
    return parent == QModelIndex() ? d->feedbacks.count() : 0;
}

QVariant FeedbackModel::data( const QModelIndex& index, int role ) const
{
    if ( index.isValid() ) {
        const Feedback feedback = this->feedback( index );
        
        switch ( role ) {
            case Qt::DisplayRole:
            case Qt::EditRole: {
				switch ( index.column() ) {
					case 0:
						return feedback.dateTime().toString( Qt::DefaultLocaleLongDate );
					case 1:
						return feedback.message();
				}
                
                break;
            }
			
			case Qt::ToolTipRole:
            case Qt::WhatsThisRole: {
				return QString( "<b>%1:</b> %2\n<b>%3:</b> %4" )
					.arg( tr( "Date time" ) )
					.arg( feedback.dateTime().toString( Qt::DefaultLocaleLongDate ) )
					.arg( tr( "Message" ) )
					.arg( feedback.message() )
					.replace( "\n", "<br />" )
				;
            }
			
			case FeedbackModel::DateTimeRole: {
				return feedback.dateTime();
			}
			
			case FeedbackModel::MessageRole: {
				return feedback.message();
			}
			
			case FeedbackModel::FeedbackRole: {
				return feedback;
			}
        }
    }
    
    return QVariant();
}

QVariant FeedbackModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole && section >= 0 && section < columnCount() ) {
        switch ( section ) {
            case 0:
                return tr( "Date time" );
			case 1:
                return tr( "Message" );
        }
    }
    
    return QAbstractTableModel::headerData( section, orientation, role );
}

void FeedbackModel::sort( int column, Qt::SortOrder order )
{
	if ( rowCount() == 0 ) {
		return;
	}
	
	emit layoutAboutToBeChanged();
	
	const QModelIndexList oldIndexes = persistentIndexList();
	QModelIndexList newIndexes;
	
	QMap<int, Feedback> oldMapping;
	QMap<Feedback, int> newMapping;
	
	for ( int i = 0; i < d->feedbacks.count(); i++ ) {
		oldMapping[ i ] = d->feedbacks[ i ];
	}
	
	switch ( order ) {
		case Qt::AscendingOrder: {
			if ( column == 0 ) {
				qSort( d->feedbacks.begin(), d->feedbacks.end() );
			}
			else if ( column == 1 ) {
				qSort( d->feedbacks.begin(), d->feedbacks.end(), FeedbackModelPrivate::lessThanMessage );
			}
			
			break;
		}
		
		case Qt::DescendingOrder: {
			if ( column == 0 ) {
				qSort( d->feedbacks.begin(), d->feedbacks.end(), qGreater<Feedback>() );
			}
			else if ( column == 1 ) {
				qSort( d->feedbacks.begin(), d->feedbacks.end(), FeedbackModelPrivate::greaterThanMessage );
			}
			
			break;
		}
	}
	
	for ( int i = 0; i < d->feedbacks.count(); i++ ) {
		newMapping[ d->feedbacks[ i ] ] = i;
	}
	
	for ( int i = 0; i < oldIndexes.count(); i++ ) {
		const QModelIndex& index = oldIndexes[ i ];
		const Feedback& feedback = oldMapping[ index.row() ];
		newIndexes << QAbstractTableModel::index( newMapping[ feedback ], index.column() );
	}
	
	changePersistentIndexList( oldIndexes, newIndexes );
	
	emit layoutChanged();
}

void FeedbackModel::clear()
{
    const int count = d->feedbacks.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginRemoveRows( QModelIndex(), 0, count -1 );
    d->feedbacks.clear();
    endRemoveRows();
}

void FeedbackModel::addFeedbacks( const Feedback::List& feedbacks )
{
	const int rcount = rowCount();
	const int count = feedbacks.count();
    
    if ( count == 0 ) {
		return;
	}
    
    beginInsertRows( QModelIndex(), rcount, rcount +count -1 );
    d->feedbacks << feedbacks;
    endInsertRows();
	sort( 0 );
}

void FeedbackModel::addFeedback( const Feedback& feedback )
{
	addFeedbacks( Feedback::List() << feedback );
}

void FeedbackModel::setFeedbacks( const Feedback::List& feedbacks )
{
    clear();
	addFeedbacks( feedbacks );
}

void FeedbackModel::updateFeedback( const QModelIndex& index, const Feedback& feedback )
{
	if ( !index.isValid() || index.row() < 0 || index.row() >= rowCount() ) {
		return;
	}
	
	d->feedbacks[ index.row() ] = feedback;
	emit dataChanged( index, index );
	sort( 0 );
}

void FeedbackModel::removeFeedbacks( const QModelIndexList& _indexes )
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
		
		d->feedbacks.removeAt( index.row() );
	}
	
	changePersistentIndexList( oldIndexes, newIndexes );
	
	emit layoutChanged();
}

void FeedbackModel::removeFeedback( const QModelIndex& index )
{
	removeFeedbacks( QModelIndexList() << index );
}

Feedback::List FeedbackModel::feedbacks() const
{
    return d->feedbacks;
}

Feedback FeedbackModel::feedback( const QModelIndex& index ) const
{
    return d->feedbacks.value( index.row() );
}

QModelIndex FeedbackModel::modelIndex( const Feedback& feedback, int column ) const
{
	return index( d->feedbacks.indexOf( feedback ), column );
}

bool FeedbackModel::loadData( const QString& filePath )
{
	return false;
}

bool FeedbackModel::saveData( const QString& filePath ) const
{
	return false;
}

void FeedbackModel::update()
{
	if ( rowCount() == 0 ) {
		return;
	}
	
	emit dataChanged( index( 0, 0 ), index( rowCount() -1, columnCount() -1 ) );
}
