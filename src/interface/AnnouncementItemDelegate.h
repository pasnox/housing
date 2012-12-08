/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : AnnouncementItemDelegate.h
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
#ifndef ANNOUNCEMENTITEMDELEGATE_H
#define ANNOUNCEMENTITEMDELEGATE_H

#include <QStyledItemDelegate>

class AnnouncementItemDelegatePrivate;
class QAbstractItemView;

class AnnouncementItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    
public:
    AnnouncementItemDelegate( QAbstractItemView* parent );
    virtual ~AnnouncementItemDelegate();
    
    virtual void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
    virtual QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const;

private:
    AnnouncementItemDelegatePrivate* d;
};

#endif // ANNOUNCEMENTITEMDELEGATE_H
