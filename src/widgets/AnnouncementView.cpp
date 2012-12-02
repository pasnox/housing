#include "AnnouncementView.h"
#include "interface/AnnouncementItemDelegate.h"

#include <QHeaderView>
#include <QDebug>

class AnnouncementViewPrivate : public QObject {
    Q_OBJECT

public:
    AnnouncementView* widget;
    QHeaderView* header;
	int headerHeight;
    
public:
    AnnouncementViewPrivate( AnnouncementView* _widget )
        : QObject( _widget ),
            widget( _widget ),
            header( new QHeaderView( Qt::Horizontal, _widget ) ),
			headerHeight( -1 )
    {
        header->setResizeMode( QHeaderView::Stretch );
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
	d->headerHeight = d->header->sizeHint().height();
    
    if ( hasModel ) {
        oldSelectionModel->deleteLater();
    }
}

void AnnouncementView::resizeEvent( QResizeEvent* event )
{
	QListView::resizeEvent( event );
	
	const QRect rect = QRect( QPoint( frameWidth(), frameWidth() ), QSize( viewport()->width(), d->headerHeight == -1 ? 21 : d->headerHeight ) );
	setViewportMargins( 0, rect.height(), 0, 0 );
	d->header->setGeometry( rect );
}

#include "AnnouncementView.moc"
