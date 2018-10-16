/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : SeLogerHousingDriver.cpp
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
#include "SeLogerHousingDriver.h"
#include "SeLogerCityQuery.h"
#include "SeLogerDistrictQuery.h"

#include <QStringList>
#include <QXmlQuery>
#include <QXmlResultItems>
#include <QFile>
#include <QApplication>
#include <QDebug>

class SeLogerHousingDriverPrivate {
public:
    SeLogerHousingDriverPrivate() {
    }
    
    QString webServiceUrl() const {
        return "http://ws.seloger.com/search.xml";
    }
};

SeLogerHousingDriver::SeLogerHousingDriver( QObject* parent )
    : AbstractHousingDriver( parent ),
        d( new SeLogerHousingDriverPrivate )
{
    Q_UNUSED( QT_TR_NOOP( "All" ) );
}

SeLogerHousingDriver::~SeLogerHousingDriver()
{
    delete d;
}

QString SeLogerHousingDriver::name() const
{
    return "SeLoger.com";
}

AbstractHousingDriver::SearchTypes SeLogerHousingDriver::supportedSearchTypes() const
{
    return
        AbstractHousingDriver::SearchTypePurchase |
        AbstractHousingDriver::SearchTypeRent
    ;
}

AbstractHousingDriver::SearchSorting SeLogerHousingDriver::supportedSearchSorting() const
{
    return
        AbstractHousingDriver::SearchSortingAscendingDate |
        AbstractHousingDriver::SearchSortingDescendingDate |
        AbstractHousingDriver::SearchSortingAscendingPrice |
        AbstractHousingDriver::SearchSortingDescendingPrice |
        AbstractHousingDriver::SearchSortingAscendingSurface |
        AbstractHousingDriver::SearchSortingDescendingSurface
    ;
}

AbstractHousingDriver::SearchProperties SeLogerHousingDriver::supportedSearchProperties() const
{
    return
        AbstractHousingDriver::SearchPropertyApartment |
        AbstractHousingDriver::SearchPropertyHouseOrVilla |
        AbstractHousingDriver::SearchPropertyParkingOrBox |
        AbstractHousingDriver::SearchPropertyGround |
        AbstractHousingDriver::SearchPropertyShop |
        AbstractHousingDriver::SearchPropertyCommercialLocal |
        AbstractHousingDriver::SearchPropertyOffices |
        AbstractHousingDriver::SearchPropertyLoftOrWorkshopOrSurface |
        AbstractHousingDriver::SearchPropertyTenement |
        AbstractHousingDriver::SearchPropertyBuilding |
        AbstractHousingDriver::SearchPropertyCastle |
        AbstractHousingDriver::SearchPropertyMansion |
        AbstractHousingDriver::SearchPropertyOthers
    ;
}

AbstractHousingDriver::SearchInputs SeLogerHousingDriver::supportedSearchInputs() const
{
    return
        AbstractHousingDriver::SearchInputNumberOfRooms |
        AbstractHousingDriver::SearchInputNumberOfBedrooms |
        AbstractHousingDriver::SearchInputMinimumBudget |
        AbstractHousingDriver::SearchInputMaximumBudget |
        AbstractHousingDriver::SearchInputMinimumSurface |
        AbstractHousingDriver::SearchInputMaximumSurface |
        AbstractHousingDriver::SearchInputMinimumGround |
        AbstractHousingDriver::SearchInputMaximumGround
    ;
}

AbstractHousingDriver::SearchFeatures SeLogerHousingDriver::supportedSearchFeatures() const
{
    return
        AbstractHousingDriver::SearchFeatureElevator |
        AbstractHousingDriver::SearchFeatureDigicode |
        AbstractHousingDriver::SearchFeatureIntercom |
        AbstractHousingDriver::SearchFeatureCaretaker |
        AbstractHousingDriver::SearchFeaturePool |
        AbstractHousingDriver::SearchFeatureTerrace |
        AbstractHousingDriver::SearchFeatureBalcony |
        AbstractHousingDriver::SearchFeatureParking |
        AbstractHousingDriver::SearchFeatureBox |
        AbstractHousingDriver::SearchFeatureCellar
    ;
}

AbstractCityQuery* SeLogerHousingDriver::cityQuery() const
{
    return new SeLogerCityQuery( QApplication::instance() );
}

AbstractDistrictQuery* SeLogerHousingDriver::districtQuery() const
{
    return new SeLogerDistrictQuery( QApplication::instance() );
}

QMap<QString, QString> SeLogerHousingDriver::roomsInputs() const
{
    QMap<QString, QString> rooms;
    rooms[ tr( "All" ) ] = "all";
    rooms[ "1" ] = "1";
    rooms[ "2" ] = "2";
    rooms[ "3" ] = "3";
    rooms[ "4" ] = "4";
    rooms[ "5+" ] = "+5";
    return rooms;
}

QMap<QString, QString> SeLogerHousingDriver::bedroomsInputs() const
{
    QMap<QString, QString> bedrooms;
    bedrooms[ tr( "All" ) ] = "all";
    bedrooms[ "1" ] = "1";
    bedrooms[ "2" ] = "2";
    bedrooms[ "3" ] = "3";
    bedrooms[ "4" ] = "4";
    bedrooms[ "5+" ] = "+5";
    return bedrooms;
}

bool SeLogerHousingDriver::isOwnUrl( const QUrl& url ) const
{
    return url.toString().startsWith( d->webServiceUrl(), Qt::CaseInsensitive );
}

QByteArray SeLogerHousingDriver::testCase() const
{
    QFile file( ":/SeLoger.com/testcase.xml" );
    
    if ( !file.open( QIODevice::ReadOnly ) ) {
        return QByteArray();
    }
    
    return file.readAll();
}

QString SeLogerHousingDriver::xPathQuery() const
{
    QFile file( ":/SeLoger.com/xquery.xq" );
    
    if ( !file.open( QIODevice::ReadOnly ) ) {
        return QString::null;
    }
    
    return QString::fromUtf8( file.readAll() );
}

void SeLogerHousingDriver::setUpSearchRequest( QNetworkRequest& request, QByteArray& data, const AbstractHousingDriver::RequestProperties& properties, int page ) const
{
    Q_UNUSED( data );
    
    QUrl url( d->webServiceUrl() );
    QStringList cities;
    QStringList districts;
    QStringList types;
    QStringList rooms;
    QStringList bedrooms;
    
    foreach ( const City& city, properties.cities ) {
        cities << city.value();
    }
    
    foreach ( const District& district, properties.districts ) {
        districts << district.value();
		if ( !cities.contains(district.valuesup()) ) {
			cities << district.valuesup();
		}
    }
    
    foreach ( const QVariant& variant, properties.numberOfRooms() ) {
        rooms << variant.toString();
    }
    
    foreach ( const QVariant& variant, properties.numberOfBedrooms() ) {
        bedrooms << variant.toString();
    }
    
    if ( properties.properties & AbstractHousingDriver::SearchPropertyApartment ) {
        types << "1";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyHouseOrVilla ) {
        types << "2";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyParkingOrBox ) {
        types << "3";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyGround ) {
        types << "4";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyShop ) {
        types << "6";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyCommercialLocal ) {
        types << "7";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyOffices ) {
        types << "8";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyLoftOrWorkshopOrSurface ) {
        types << "9";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyTenement ) {
        types << "11";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyBuilding ) {
        types << "12";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyCastle ) {
        types << "13";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyMansion ) {
        types << "14";
    }

    if ( properties.properties & AbstractHousingDriver::SearchPropertyOthers ) {
        types << "15";
    }
    
    switch ( properties.type ) {
        case AbstractHousingDriver::SearchTypeRent:
            url.addQueryItem( "idtt", "1" );
            break;
        case AbstractHousingDriver::SearchTypePurchase:
            url.addQueryItem( "idtt", "2" );
            break;
        default:
            break;
    }
    
    url.addQueryItem( "ci", cities.join( "," ) );
    url.addQueryItem( "idq", districts.join( "," ) );
    
    if ( properties.properties != AbstractHousingDriver::SearchPropertyNone ) {
        url.addQueryItem( "idtypebien", types.join( "," ) );
    }
    
    url.addQueryItem( "nb_pieces", rooms.join( "," ) );
    url.addQueryItem( "nb_chambres", bedrooms.join( "," ) );
    
    if ( properties.minimumBudget() > 0 ) {
        url.addQueryItem( "pxmin", QString::number( properties.minimumBudget() ) );
    }
    
    if ( properties.maximumBudget() > 0 ) {
        url.addQueryItem( "pxmax", QString::number( properties.maximumBudget() ) );
    }
    
    if ( properties.minimumSurface() > 0 ) {
        url.addQueryItem( "surfacemin", QString::number( properties.minimumSurface() ) );
    }
    
    if ( properties.maximumSurface() > 0 ) {
        url.addQueryItem( "surfacemax", QString::number( properties.maximumSurface() ) );
    }
    
    if ( properties.minimumGround() > 0 ) {
        url.addQueryItem( "surf_terrainmin", QString::number( properties.minimumGround() ) );
    }
    
    if ( properties.maximumGround() > 0 ) {
        url.addQueryItem( "surf_terrainmax", QString::number( properties.maximumGround() ) );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureElevator ) {
        url.addQueryItem( "si_ascenseur", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureDigicode ) {
        url.addQueryItem( "si_digicode", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureIntercom ) {
        url.addQueryItem( "si_interphone", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureCaretaker ) {
        url.addQueryItem( "si_gardien", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeaturePool ) {
        url.addQueryItem( "si_piscine", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureTerrace ) {
        url.addQueryItem( "si_terrasse", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureBalcony ) {
        url.addQueryItem( "nb_balconsmin", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureParking ) {
        url.addQueryItem( "si_parkings", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureBox ) {
        url.addQueryItem( "si_boxes", "1" );
    }
    
    if ( properties.features & AbstractHousingDriver::SearchFeatureCellar ) {
        url.addQueryItem( "si_cave", "1" );
    }
    
    switch ( properties.sorting ) {
        case AbstractHousingDriver::SearchSortingNone:
        case AbstractHousingDriver::SearchSortingAll:
            break;
        case AbstractHousingDriver::SearchSortingAscendingDate:
            url.addQueryItem( "tri", "a_dt_crea" );
            break;
        case AbstractHousingDriver::SearchSortingDescendingDate:
            url.addQueryItem( "tri", "d_dt_crea" );
            break;
        case AbstractHousingDriver::SearchSortingAscendingPrice:
            url.addQueryItem( "tri", "a_px" );
            break;
        case AbstractHousingDriver::SearchSortingDescendingPrice:
            url.addQueryItem( "tri", "d_px" );
            break;
        case AbstractHousingDriver::SearchSortingAscendingSurface:
            url.addQueryItem( "tri", "a_surface" );
            break;
        case AbstractHousingDriver::SearchSortingDescendingSurface:
            url.addQueryItem( "tri", "d_surface" );
            break;
    }
    
    if ( page > 1 ) {
        url.addQueryItem( "SEARCHpg", QString::number( page ) );
    }
    
    //qWarning( "%s: %s", Q_FUNC_INFO, qPrintable( url.toString() ) );
    
    request.setUrl( url );
}

bool SeLogerHousingDriver::parseSearchRequestData( const QByteArray& data, Announcement::List& announcements, RequestResultProperties* properties ) const
{
    // before parsing the announce, we convert the xml to a standard simple one using xquery
    const QString xpath = xPathQuery();
    QXmlQuery query;
    QString xml;
    
    if ( !query.setFocus( QString::fromUtf8( data ) ) ) {
        if ( properties ) {
            properties->error = tr( "%s: Can't set focus" ).arg( Q_FUNC_INFO );
        }
        
        qWarning( "%s: 1", Q_FUNC_INFO );
        return false;
    }

    query.setQuery( xpath, QUrl( d->webServiceUrl() ) );
    
    if ( !query.isValid() ) {
        if ( properties ) {
            properties->error = tr( "%s: Invalid query" ).arg( Q_FUNC_INFO );
        }
        
        qWarning( "%s: 2", Q_FUNC_INFO );
        return false;
    }
    
    if ( !query.evaluateTo( &xml ) ) {
        if ( properties ) {
            properties->error = tr( "%s: Can't evaluateTo" ).arg( Q_FUNC_INFO );
        }
        
        qWarning( "%s: 3", Q_FUNC_INFO );
        return false;
    }
    
    return parseStandardDomDocument( xml, announcements, properties );
}
