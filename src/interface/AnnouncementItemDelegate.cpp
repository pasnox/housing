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
#include <QDebug>

class AnnouncementItemDelegatePrivate {
public:
    QAbstractItemView* view;
    QLabel* label;
    int margin;
    int iconMargin;
    QIcon ignoredIcon;
    QIcon bookmarkedIcon;

public:
    AnnouncementItemDelegatePrivate( QAbstractItemView* _view )
        : view( _view ),
            label( new QLabel ),
            margin( 5 ),
            iconMargin( 5 ),
            ignoredIcon( QIcon::fromTheme( "edit-clear-list" ) ),
            bookmarkedIcon( QIcon::fromTheme( "bookmarks" ) )
    {
        label->setTextFormat( Qt::RichText );
        label->setAlignment( Qt::AlignLeft | Qt::AlignTop );
        label->setWordWrap( true );
    }
    
    ~AnnouncementItemDelegatePrivate() {
        delete label;
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

QString AnnouncementItemDelegate::displayText( const QVariant& value, const QLocale& locale ) const
{
    Q_UNUSED( value );
    Q_UNUSED( locale );
    return QString::null;
}

void AnnouncementItemDelegate::paint( QPainter* painter, const QStyleOptionViewItem& _option, const QModelIndex& index ) const
{
    const bool ignored = index.data( AnnouncementModel::IgnoredRole ).toBool();
    const bool bookmarked = index.data( AnnouncementModel::BookmarkedRole ).toBool();
    QStyleOptionViewItemV4 option = *qstyleoption_cast<const QStyleOptionViewItemV4*>( &_option );
    
    option.font.setPointSize( option.font.pointSize() -1 );
    
    if ( option.state & QStyle::State_HasFocus ) {
        option.state ^= QStyle::State_HasFocus;
    }
    
    if ( ignored ) {
        if ( option.state & QStyle::State_Selected ) {
            option.state ^= QStyle::State_Selected;
            option.state |= QStyle::State_MouseOver;
        }
        
        option.palette.setColor( QPalette::WindowText, option.palette.color( QPalette::Disabled, QPalette::WindowText ) );
        option.font.setStrikeOut( true );
    }
    else if ( bookmarked ) {
        option.font.setBold( true );
    }
    else {
        option.palette.setColor( QPalette::WindowText, QColor( Qt::darkBlue ) );
    }
    
    QStyledItemDelegate::paint( painter, option, index );
    
    if ( !index.isValid() ) {
        return;
    }
    
    const Announcement announcement = index.data( AnnouncementModel::AnnouncementRole ).value<Announcement>();
    const QSize pixmapSize = index.data( Qt::DecorationRole ).value<QPixmap>().size();
    const QSize size = sizeHint( option, index );
    const QString text = index.data( Qt::ToolTipRole ).toString();
    QIcon icon;
    
    if ( ignored ) {
        icon = d->ignoredIcon;
    }
    
    if ( bookmarked ) {
        icon = d->bookmarkedIcon;
    }
    
    if ( !icon.isNull() ) {
        icon.paint( painter, QRect( option.rect.topLeft() +QPoint( d->margin +d->iconMargin, d->margin +d->iconMargin ), QSize( 22, 22 ) ) );
    }
    
    painter->save();
    painter->translate( option.rect.topLeft() +QPoint( pixmapSize.width() +d->margin, d->margin ) );
    d->label->resize( size -QSize( pixmapSize.width(), 0 ) -QSize( d->margin *2, d->margin *2 ) );
    d->label->setPalette( option.palette );
    d->label->setFont( option.font );
    d->label->setText( text );
    d->label->ensurePolished();
    d->label->render( painter, QPoint(), QRegion(), QWidget::DrawChildren );
    painter->restore();
}

QSize AnnouncementItemDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    Q_UNUSED( option );
    Q_UNUSED( index );
    return QSize( d->view->viewport()->width(), d->view->iconSize().height() +( d->margin *2 ) );
}
