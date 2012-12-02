/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : SeLogerHousingDriver.h
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
#ifndef SELOGERHOUSINGDRIVER_H
#define SELOGERHOUSINGDRIVER_H

#include "interface/AbstractHousingDriver.h"

class SeLogerHousingDriverPrivate;

class SeLogerHousingDriver : public AbstractHousingDriver
{
    Q_OBJECT
    
public:
    SeLogerHousingDriver( QObject* parent = 0 );
    virtual ~SeLogerHousingDriver();
    
    virtual QString name() const;
    
    virtual AbstractHousingDriver::SearchTypes supportedSearchTypes() const;
    virtual AbstractHousingDriver::SearchSorting supportedSearchSorting() const;
    virtual AbstractHousingDriver::SearchProperties supportedSearchProperties() const;
    virtual AbstractHousingDriver::SearchInputs supportedSearchInputs() const;
    virtual AbstractHousingDriver::SearchFeatures supportedSearchFeatures() const;
    
    virtual AbstractCityQuery* cityQuery() const;
    virtual QMap<QString, QString> roomsInputs() const;
    virtual QMap<QString, QString> bedroomsInputs() const;
    virtual bool isOwnUrl( const QUrl& url ) const;
    virtual QByteArray testCase() const;
    virtual QString xPathQuery() const;
    virtual void setUpSearchRequest( QNetworkRequest& request, QByteArray& data, const AbstractHousingDriver::RequestProperties& properties, int page ) const;
    virtual bool parseSearchRequestData( const QByteArray& data, Announcement::List& announcements, RequestResultProperties* properties = 0 ) const;

private:
    SeLogerHousingDriverPrivate* d;
};

#endif // SELOGERHOUSINGDRIVER_H
