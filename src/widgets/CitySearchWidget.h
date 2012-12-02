/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : CitySearchWidget.h
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
#ifndef CITYSEARCHWIDGET_H
#define CITYSEARCHWIDGET_H

#include <QWidget>

#include "interface/City.h"

class QEvent;
class AbstractCityQuery;
class CitySearchWidgetPrivate;

class CitySearchWidget : public QWidget
{
    Q_OBJECT

public:
    CitySearchWidget( QWidget* parent = 0 );
    virtual ~CitySearchWidget();
    
    void setCityQuery( AbstractCityQuery* query );
    AbstractCityQuery* cityQuery() const;
    
    void setCities( const City::List& cities );
    City::List cities() const;
    
    void setCodeVisible( bool visible );
    bool isCodeVisible() const;

protected:
    virtual void changeEvent( QEvent* event );

private:
    CitySearchWidgetPrivate* d;
};

#endif // CITYSEARCHWIDGET_H
