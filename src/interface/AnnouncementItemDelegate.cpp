/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : AnnouncementItemDelegate.cpp
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
#include "AnnouncementItemDelegate.h"
#include "AnnouncementModel.h"

#include <QAbstractItemView>
#include <QLabel>
#include <QPainter>
#include <QApplication>
#include <QAbstractTextDocumentLayout>
#include <QTimer>
#include <QDebug>

class AnnouncementItemDelegatePrivate {
public:
    QAbstractItemView* view;
    QTextDocument document;
    int margin;
    int iconMargin;
    QIcon ignoredIcon;
    QIcon bookmarkedIcon;
    QMap<QPersistentModelIndex, int> heights;
    QTimer timer;

public:
    AnnouncementItemDelegatePrivate( QAbstractItemView* _view )
        : view( _view ),
            margin( 7 ),
            iconMargin( 8 ),
            ignoredIcon( QIcon::fromTheme( "edit-clear-list" ) ),
            bookmarkedIcon( QIcon::fromTheme( "bookmarks" ) )
    {
        QTextOption option;
        option.setAlignment( Qt::AlignLeft | Qt::AlignTop );
        option.setWrapMode( QTextOption::WrapAtWordBoundaryOrAnywhere );
        option.setTabStop( 40 );
        
        document.setDefaultTextOption( option );
        document.setDocumentMargin( margin );
        
        timer.setInterval( 250 );
        timer.setSingleShot( true );
        
        QObject::connect( &timer, SIGNAL( timeout() ), view->model(), SLOT( update() ) );
    }
    
    ~AnnouncementItemDelegatePrivate() {
    }
    
    QStyleOptionViewItemV4 styleOptions( const QStyleOptionViewItem& _option, const QModelIndex& index, QIcon* iconState = 0 ) const {
        const bool ignored = index.data( AnnouncementModel::IgnoredRole ).toBool();
        const bool bookmarked = index.data( AnnouncementModel::BookmarkedRole ).toBool();
        QStyleOptionViewItemV4 option = *qstyleoption_cast<const QStyleOptionViewItemV4*>( &_option );
        
        if ( option.state & QStyle::State_HasFocus ) {
            option.state ^= QStyle::State_HasFocus;
        }
        
        if ( ignored ) {
            if ( option.state & QStyle::State_Selected ) {
                option.state ^= QStyle::State_Selected;
                option.state |= QStyle::State_MouseOver;
            }
            
            option.palette.setColor( QPalette::Text, option.palette.color( QPalette::Disabled, QPalette::WindowText ) );
            option.font.setStrikeOut( true );
            
            if ( iconState ) {
                *iconState = ignoredIcon;
            }
        }
        else if ( bookmarked ) {
            option.font.setBold( true );
            
            if ( iconState ) {
                *iconState = bookmarkedIcon;
            }
        }
        else {
            option.palette.setColor( QPalette::Text, QColor( Qt::darkBlue ) );
        }
        
        option.font.setPointSize( option.font.pointSize() -1 );
        option.text = QString::null;
        return option;
    }
    
    QStyleOptionViewItemV4 setupDocument( const QStyleOptionViewItem& _option, const QModelIndex& index, QAbstractTextDocumentLayout::PaintContext* context = 0, QIcon* iconState = 0 ) {
        const QStyleOptionViewItemV4 option = styleOptions( _option, index, iconState );
        document.setDefaultFont( option.font );
        document.setHtml( index.data( Qt::ToolTipRole ).toString() );
        document.setTextWidth( view->viewport()->width() -view->iconSize().width() -( iconMargin *2 ) );
        
        if ( context ) {
            context->palette = option.palette;
    
            if ( option.state & QStyle::State_Selected ) {
                context->palette.setColor( QPalette::Text, option.palette.color( QPalette::Active, QPalette::HighlightedText ) );
            }
        }
        
        return option;
    }
};

AnnouncementItemDelegate::AnnouncementItemDelegate( QAbstractItemView* parent )
    : QStyledItemDelegate( parent ),
        d( new AnnouncementItemDelegatePrivate( parent ) )
{
}

AnnouncementItemDelegate::~AnnouncementItemDelegate()
{
    delete d;
}

void AnnouncementItemDelegate::paint( QPainter* painter, const QStyleOptionViewItem& _option, const QModelIndex& index ) const
{
    QAbstractTextDocumentLayout::PaintContext context;
    QIcon iconState;
    QStyleOptionViewItemV4 option = d->setupDocument( _option, index, &context, &iconState );
    const Announcement announcement = index.data( AnnouncementModel::AnnouncementRole ).value<Announcement>();
    const QStyle* style = option.widget ? option.widget->style() : QApplication::style();
    const QRect textRect( option.rect.adjusted( d->view->iconSize().width() +( d->iconMargin *2 ), 0, 0, 0 ) );
    const QPixmap pixmap = index.data( Qt::DecorationRole ).value<QPixmap>();
    
    option.rect = option.rect.adjusted( 1, 1, -1, -1 );
    style->drawControl( QStyle::CE_ItemViewItem, &option, painter );
    
    if ( index.row() >= 0 && index.row() < index.model()->rowCount( index.parent() ) -1 ) {
        option.rect = _option.rect.adjusted( pixmap.width() +( d->iconMargin *2 ), _option.rect.height() -1, 0, 0 );
        style->drawPrimitive( QStyle::PE_IndicatorToolBarSeparator, &option, painter );
    }
    
    option.rect = _option.rect;
    
    painter->save();
    painter->setRenderHint( QPainter::Antialiasing );
    
    painter->setPen( QPen( QColor( 0, 0, 0 ), 0.4 ) );
    painter->setBrush( QColor( 150, 150, 150, 80 ) );
    painter->drawRoundedRect( QRect( option.rect.topLeft() +( QPoint( d->iconMargin, d->iconMargin ) /2 ), pixmap.size() +QSize( d->iconMargin, d->iconMargin ) ), 5, 5 );
    
    if ( !pixmap.isNull() ) {
        painter->drawPixmap( option.rect.topLeft() +QPoint( d->iconMargin, d->iconMargin ), pixmap );
    }
    
    if ( !iconState.isNull() ) {
        iconState.paint( painter, QRect( option.rect.topLeft() +QPoint( d->margin +d->iconMargin, d->margin +d->iconMargin ), QSize( 22, 22 ) ) );
    }
    
    painter->translate( textRect.topLeft() );
    painter->setClipRect( textRect.translated( -textRect.topLeft() ) );
    d->document.documentLayout()->draw( painter, context );
    painter->restore();
}

QSize AnnouncementItemDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    d->setupDocument( option, index );
    const QSize pixmapSize( d->view->iconSize() +QSize( d->iconMargin *2, d->iconMargin *2 ) );
    const QSize documentSize( d->document.idealWidth(), d->document.size().toSize().height() );
    const QSize size( pixmapSize.width() + documentSize.width(), qMax( pixmapSize.height(), documentSize.height() ) );
    
    if ( d->heights[ index ] != size.height() ) {
        d->heights[ index ] = size.height();
        d->timer.start();
    }
    
    return size;
}
