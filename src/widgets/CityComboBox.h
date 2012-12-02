/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : CityComboBox.h
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
#ifndef CITYCOMBOBOX_H
#define CITYCOMBOBOX_H

#include "FreshGui/pComboBox"

#include "interface/City.h"

class CityComboBoxPrivate;
class AbstractCityQuery;

class CityComboBox : public pComboBox
{
    Q_OBJECT
    
public:
    CityComboBox( QWidget* parent = 0 );
    virtual ~CityComboBox();
    
    void setCityQuery( AbstractCityQuery* query );
    AbstractCityQuery* cityQuery() const;
    
    City city() const;

private:
    CityComboBoxPrivate* d;
};

#endif // CITYCOMBOBOX_H
