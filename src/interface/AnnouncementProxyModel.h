/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : AnnouncementProxyModel.h
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
#ifndef ANNOUNCEMENTPROXYMODEL_H
#define ANNOUNCEMENTPROXYMODEL_H

#include <QSortFilterProxyModel>

class AnnouncementProxyModelPrivate;
class AnnouncementModel;
class QAction;

class AnnouncementProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    
public:
    AnnouncementProxyModel( AnnouncementModel* parent );
    virtual ~AnnouncementProxyModel();
    
    QAction* filterAction() const;

public slots:
    void update();

protected:
    virtual bool filterAcceptsRow( int sourceRow, const QModelIndex & sourceParent ) const;

private:
    AnnouncementProxyModelPrivate* d;

signals:
    void changed();
    void rowCountChanged( int count );
};

#endif // ANNOUNCEMENTPROXYMODEL_H
