#include "AnnouncementView.h"
#include "interface/AnnouncementItemDelegate.h"

#include <QHeaderView>

#define AnnouncementViewPrivateHeaderHeight 21

class AnnouncementViewPrivate : public QObject {
    Q_OBJECT

public:
    AnnouncementView* widget;
    QHeaderView* header;
    
public:
    AnnouncementViewPrivate( AnnouncementView* _widget )
        : QObject( _widget ),
            widget( _widget ),
            header( new QHeaderView( Qt::Horizontal, _widget ) )
    {
        header->setResizeMode( QHeaderView::ResizeToContents );
        header->setClickable( true );
        header->setSortIndicatorShown( true );
        
        connect( header, SIGNAL( sortIndicatorChanged( int, Qt::SortOrder ) ), this, SLOT( header_sortIndicatorChanged( int, Qt::SortOrder ) ) );
    }

public slots:
    void header_sortIndicatorChanged( int logicalIndex, Qt::SortOrder order ) {
        widget->model()->sort( logicalIndex, order );
        
        if ( widget->selectionModel()->hasSelection() ) {
            widget->scrollTo( widget->selectionModel()->selectedIndexes().last() );
        }
    }
};

AnnouncementView::AnnouncementView( QWidget* parent )
    : QListView( parent ),
        d( new AnnouncementViewPrivate( this ) )
{
    setViewportMargins( 0, AnnouncementViewPrivateHeaderHeight, 0, 0 );
    setItemDelegate( new AnnouncementItemDelegate( this ) );
}

AnnouncementView::~AnnouncementView()
{
}

QHeaderView* AnnouncementView::header() const
{
    return d->header;
}

void AnnouncementView::setModel( QAbstractItemModel* model )
{
    const bool hasModel = this->model() != 0;
    QItemSelectionModel* oldSelectionModel;
    
    oldSelectionModel = selectionModel();
    QListView::setModel( model );
    
    if ( hasModel ) {
        oldSelectionModel->deleteLater();
    }
    
    oldSelectionModel = d->header->selectionModel();
    d->header->setModel( model );
    d->header->setSelectionModel( selectionModel() );
    
    if ( hasModel ) {
        oldSelectionModel->deleteLater();
    }
}

void AnnouncementView::resizeEvent( QResizeEvent* event )
{
	QListView::resizeEvent( event );
	
	QRect rect = QRect( QPoint( frameWidth(), frameWidth() ), QSize( viewport()->width(), AnnouncementViewPrivateHeaderHeight ) );
	d->header->setGeometry( rect );
}

#include "AnnouncementView.moc"
