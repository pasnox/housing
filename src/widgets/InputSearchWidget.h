/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : InputSearchWidget.h
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
#ifndef INPUTSEARCHWIDGET_H
#define INPUTSEARCHWIDGET_H

#include <QScrollArea>
#include <QSet>

#include "interface/AbstractHousingDriver.h"

class InputSearchWidgetPrivate;
class QEvent;

class InputSearchWidget : public QScrollArea
{
    Q_OBJECT

public:
    InputSearchWidget( QWidget* parent = 0 );
    virtual ~InputSearchWidget();
    
    void setCurrentDriver( AbstractHousingDriver* driver );
    AbstractHousingDriver* currentDriver() const;
    
    void setCurrentDriverName( const QString& name );
    QString currentDriverName() const;
    
    void setIgnoredId( int id, bool ignored );
    bool isIgnoredId( int id ) const;
    QSet<int> ignoredIdSet() const;
    
    void setBookmarkedId( int id, bool ignored );
    bool isBookmarkedId( int id ) const;
    QSet<int> bookmarkedIdSet() const;
    
    void setRequestProperties( const AbstractHousingDriver::RequestProperties& properties );
    AbstractHousingDriver::RequestProperties requestProperties() const;
    
    bool loadRequestProperties();
    bool saveRequestProperties() const;
    
protected:
    virtual void changeEvent( QEvent* event );

private:
    InputSearchWidgetPrivate* d;
};

#endif // INPUTSEARCHWIDGET_H
