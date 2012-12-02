/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : AnnouncementWidget.h
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
#ifndef ANNOUNCEMENTWIDGET_H
#define ANNOUNCEMENTWIDGET_H

#include <QWidget>

class Ui_AnnouncementWidget;
class QEvent;
class Announcement;

class AnnouncementWidget : public QWidget
{
    Q_OBJECT

public:
    AnnouncementWidget( QWidget* parent = 0 );
    virtual ~AnnouncementWidget();
    
    void setAnnouncement( const Announcement& announcement );

public slots:
    virtual void retranslateUi();
    
protected:
    Ui_AnnouncementWidget* ui;
    
    virtual void changeEvent( QEvent* event );
};

#endif // ANNOUNCEMENTWIDGET_H
