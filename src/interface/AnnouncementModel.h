/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : AnnouncementModel.h
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
#ifndef ANNOUNCEMENTMODEL_H
#define ANNOUNCEMENTMODEL_H

#include <QAbstractTableModel>

#include "Announcement.h"

class AnnouncementModelPrivate;

class AnnouncementModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    enum CustomRoles {
        IdRole = Qt::UserRole,
        ThumbnailRole,
        IgnoredRole,
        BookmarkedRole,
        UrlRole,
        AnnouncementRole,
        // internal, do not use
        FirstRole = IdRole,
        LastRole = AnnouncementRole
    };
    
    AnnouncementModel( QObject* parent = 0 );
    virtual ~AnnouncementModel();
    
    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    virtual bool canFetchMore( const QModelIndex& parent ) const;
    virtual void fetchMore( const QModelIndex& parent );
    
    void clear();
    void addAnnouncements( const Announcement::List& announcements );
    void addAnnouncement( const Announcement& announcement );
    void setAnnouncements( const Announcement::List& announcements );
    void removeAnnouncements( const QModelIndexList& indexes );
    void removeAnnouncement( const QModelIndex& index );
    Announcement::List announcements() const;
    Announcement announcement( const QModelIndex& index ) const;
    
    void setCanFetchMore( bool can );
    
    void setCurrentPage( int page );
    int currentPage() const;
    
    void setIgnoredIdSet( const QSet<int> ids );
    QSet<int> ignoredIdSet() const;
    
    void setBookmarkedIdSet( const QSet<int> ids );
    QSet<int> bookmarkedIdSet() const;

public slots:
    void update();

private:
    AnnouncementModelPrivate* d;

signals:
    void requestImageDownload( const QString& url );
    void requestFetchMore();
};

#endif // ANNOUNCEMENTMODEL_H
