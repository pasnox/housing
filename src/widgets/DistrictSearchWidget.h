/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : DistrictSearchWidget.h
** Date      : 2015-09-06T00:26:14
** License   : GPL3
** Home Page : https://github.com/don-vip/housing
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
#ifndef DISTRICTSEARCHWIDGET_H
#define DISTRICTSEARCHWIDGET_H

#include <QWidget>

#include "interface/District.h"

class QEvent;
class AbstractDistrictQuery;
class DistrictSearchWidgetPrivate;

class DistrictSearchWidget : public QWidget
{
    Q_OBJECT

public:
    DistrictSearchWidget( QWidget* parent = 0 );
    virtual ~DistrictSearchWidget();
    
    void setDistrictQuery( AbstractDistrictQuery* query );
    AbstractDistrictQuery* districtQuery() const;
    
    void setDistricts( const District::List& districts );
    District::List districts() const;
    
    void setCodeVisible( bool visible );
    bool isCodeVisible() const;

protected:
    virtual void changeEvent( QEvent* event );

private:
    DistrictSearchWidgetPrivate* d;
};

#endif // DISTRICTSEARCHWIDGET_H
