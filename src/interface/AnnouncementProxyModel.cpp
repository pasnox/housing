/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : AnnouncementProxyModel.cpp
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
#include "AnnouncementProxyModel.h"
#include "AnnouncementModel.h"

#include <QAction>
#include <QTimer>

class AnnouncementProxyModelPrivate : public QObject {
    Q_OBJECT

public:
    AnnouncementProxyModel* model;
    QAction* filterAction;
    QTimer* timer;

public:
    AnnouncementProxyModelPrivate( AnnouncementProxyModel* _model )
        : QObject( _model ),
            model( _model ),
            filterAction( new QAction( model ) ),
            timer( new QTimer( this ) )
    {
        filterAction->setCheckable( true );
        filterAction->setIcon( QIcon::fromTheme( "view-filter" ) );
        filterAction->setText( AnnouncementProxyModel::tr( "Show/Hide ignored announcements" ) );
        
        timer->setSingleShot( true );
        timer->setInterval( 25 );
        
        connect( filterAction, SIGNAL( triggered() ), this, SLOT( filterAction_triggered() ) );
        connect( timer, SIGNAL( timeout() ), this, SLOT( timer_timeout() ) );
        connect( model, SIGNAL( layoutAboutToBeChanged() ), timer, SLOT( start() ) );
        connect( model, SIGNAL( layoutChanged() ), timer, SLOT( start() ) );
        connect( model, SIGNAL( modelAboutToBeReset() ), timer, SLOT( start() ) );
        connect( model, SIGNAL( modelReset() ), timer, SLOT( start() ) );
        connect( model, SIGNAL( rowsAboutToBeInserted( const QModelIndex&, int, int ) ), timer, SLOT( start() ) );
        connect( model, SIGNAL( rowsAboutToBeMoved( const QModelIndex&, int, int, const QModelIndex&, int ) ), timer, SLOT( start() ) );
        connect( model, SIGNAL( rowsAboutToBeRemoved( const QModelIndex&, int, int ) ), timer, SLOT( start() ) );
        connect( model, SIGNAL( rowsInserted( const QModelIndex&, int, int ) ), timer, SLOT( start() ) );
        connect( model, SIGNAL( rowsMoved( const QModelIndex&, int, int, const QModelIndex&, int ) ), timer, SLOT( start() ) );
        connect( model, SIGNAL( rowsRemoved( const QModelIndex&, int, int ) ), timer, SLOT( start() ) );
        connect( this, SIGNAL( changed() ), model, SIGNAL( changed() ) );
        connect( this, SIGNAL( rowCountChanged( int ) ), model, SIGNAL( rowCountChanged( int ) ) );
    }

public slots:
    void filterAction_triggered() {
        model->invalidate();
    }
    
    void timer_timeout() {
        emit changed();
        emit rowCountChanged( model->rowCount() );
    }

signals:
    void changed();
    void rowCountChanged( int count );
};

AnnouncementProxyModel::AnnouncementProxyModel( AnnouncementModel* parent )
    : QSortFilterProxyModel( parent ),
        d( new AnnouncementProxyModelPrivate( this ) )
{
    Q_ASSERT( parent );
    //connect( parent, SIGNAL( changed() ), d, SIGNAL( changed() ) );
    setSourceModel( parent );
}

AnnouncementProxyModel::~AnnouncementProxyModel()
{
}

QAction* AnnouncementProxyModel::filterAction() const
{
    return d->filterAction;
}

bool AnnouncementProxyModel::filterAcceptsRow( int sourceRow, const QModelIndex & sourceParent ) const
{
    if ( d->filterAction->isChecked() ) {
        const QModelIndex index = sourceModel()->index( sourceRow, 0, sourceParent );
        return index == QModelIndex() ? true : !index.data( AnnouncementModel::IgnoredRole ).toBool();
    }
    
    return QSortFilterProxyModel::filterAcceptsRow( sourceRow, sourceParent );
}

#include "AnnouncementProxyModel.moc"
