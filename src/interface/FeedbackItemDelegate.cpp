/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : FeedbackItemDelegate.cpp
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
#include "FeedbackItemDelegate.h"
#include "FeedbackModel.h"
#include "objects/Housing.h"

#include <QAbstractItemView>
#include <QTextDocument>
#include <QPainter>
#include <QApplication>
#include <QAbstractTextDocumentLayout>
#include <QTimer>
#include <QDebug>

class FeedbackItemDelegatePrivate {
public:
    QAbstractItemView* view;
    QTextDocument document;
    int margin;
    QMap<QPersistentModelIndex, int> heights;
    QTimer timer;

public:
    FeedbackItemDelegatePrivate( QAbstractItemView* _view )
        : view( _view ),
            margin( 5 )
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
    
    ~FeedbackItemDelegatePrivate() {
    }
    
    QStyleOptionViewItemV4 styleOptions( const QStyleOptionViewItem& _option ) const {
        QStyleOptionViewItemV4 option = *qstyleoption_cast<const QStyleOptionViewItemV4*>( &_option );
        option.font.setPointSize( option.font.pointSize() -1 );
        
        if ( option.state & QStyle::State_HasFocus ) {
            option.state ^= QStyle::State_HasFocus;
        }
        
        option.text = QString::null;
        return option;
    }
    
    QStyleOptionViewItemV4 setupDocument( const QStyleOptionViewItem& _option, const QModelIndex& index, QAbstractTextDocumentLayout::PaintContext* context = 0 ) {
        const QStyleOptionViewItemV4 option = styleOptions( _option );
        document.setDefaultFont( option.font );
        document.setHtml( index.data( Qt::ToolTipRole ).toString() );
        document.setTextWidth( view->viewport()->width() );
        
        if ( context ) {
            context->palette = option.palette;
    
            if ( option.state & QStyle::State_Selected ) {
                context->palette.setColor( QPalette::Text, option.palette.color( QPalette::Active, QPalette::HighlightedText ) );
            }
        }
        
        return option;
    }
};

FeedbackItemDelegate::FeedbackItemDelegate( QAbstractItemView* parent )
    : QStyledItemDelegate( parent ),
        d( new FeedbackItemDelegatePrivate( parent ) )
{
}

FeedbackItemDelegate::~FeedbackItemDelegate()
{
    delete d;
}

void FeedbackItemDelegate::paint( QPainter* painter, const QStyleOptionViewItem& _option, const QModelIndex& index ) const
{
    QAbstractTextDocumentLayout::PaintContext context;
    const QStyleOptionViewItemV4 option = d->setupDocument( _option, index, &context );
    QStyle* style = option.widget ? option.widget->style() : QApplication::style();
    
    style->drawControl( QStyle::CE_ItemViewItem, &option, painter );
    
    painter->save();
    painter->translate( option.rect.topLeft() );
    painter->setClipRect( option.rect.translated( -option.rect.topLeft() ) );
    d->document.documentLayout()->draw( painter, context );
    painter->restore();
}

QSize FeedbackItemDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    d->setupDocument( option, index );
    const QSize size( d->document.idealWidth(), d->document.size().height() );
    
    if ( d->heights[ index ] != size.height() ) {
        d->heights[ index ] = size.height();
        d->timer.start();
    }
    
    return size;
}
