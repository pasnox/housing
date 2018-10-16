/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : SeLogerDistrictQuery.cpp
** Date      : 2015-09-05T23:32:14
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
#include "SeLogerDistrictQuery.h"
#include "objects/NetworkManager.h"
#include "objects/Housing.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QStringList>
#include <QDebug>

class SeLogerDistrictQueryPrivate : public QObject {
    Q_OBJECT

public:
    SeLogerDistrictQuery* query;
    int searchLength;

public:
    SeLogerDistrictQueryPrivate( SeLogerDistrictQuery* _query )
        : QObject( _query ),
            query( _query ),
            searchLength( 2 )
    {
        connect( NetworkManager::instance(), SIGNAL( jsonFinished( QNetworkReply*, const QByteArray&, const QVariantMap& ) ), this, SLOT( jsonFinished( QNetworkReply*, const QByteArray&, const QVariantMap& ) ) );
        connect( this, SIGNAL( districtsReceived( const District::List& ) ), query, SIGNAL( districtsReceived( const District::List& ) ) );
        connect( this, SIGNAL( error( const QString& ) ), query, SIGNAL( error( const QString& ) ) );
    }
    
    QUrl requestUrl( const QString& text ) const {
        return QUrl( QString( "http://www.seloger.com/js,ajax,villequery_v3.htm?ville=%1&mode=1" ).arg( text ) );
    }

private slots:
    void jsonFinished( QNetworkReply* reply, const QByteArray& json, const QVariantMap& data ) {
        Q_UNUSED( reply );
        Q_UNUSED( json );
        
        if ( data.value( "success" ).toBool() ) {
            const QStringList priorities = QStringList()
                << "quartier"
                << "suggestions"
            ;
            const QVariantList results = data.value( "json" ).toList();
            QVariantList districtsList;
            bool found = false;
            
            foreach ( const QString& priority, priorities ) {
                foreach ( const QVariant& variant, results ) {
                    const QVariantMap map = variant.toMap();
                    const QString label = map.value( "label" ).toString().toLower();
                    
                    if ( label == priority ) {
                        districtsList = map.value( "values" ).toList();
                        found = true;
                        break;
                    }
                }
                
                if ( found ) {
                    break;
                }
            }
            
            if ( !found ) {
                emit error( SeLogerDistrictQuery::tr( "No data found." ) );
                return;
            }
            
            District::List districts;
            
            foreach ( const QVariant& districtVariant, districtsList ) {
                const QVariantMap district = districtVariant.toMap();
                
                if ( !district.isEmpty() ) {
                    districts << District( Housing::toPlainText( district.value( "label" ).toString() ), district.value( "value" ).toString(), district.value( "code" ).toString(), district.value( "valuesup" ).toString() );
                }
            }
            
            emit districtsReceived( districts );
        }
        else {
            emit error( data.value( "message" ).toString() );
        }
    }

signals:
    void districtsReceived( const District::List& districts );
    void error( const QString& error );
};

SeLogerDistrictQuery::SeLogerDistrictQuery( QObject* parent )
    : AbstractDistrictQuery( parent ),
        d( new SeLogerDistrictQueryPrivate( this ) )
{
}

SeLogerDistrictQuery::~SeLogerDistrictQuery()
{
}

void SeLogerDistrictQuery::setMinimumSearchLength( int length )
{
    d->searchLength = length;
}

int SeLogerDistrictQuery::minimumSearchLength() const
{
    return d->searchLength;
}

void SeLogerDistrictQuery::search( const QString& text )
{
    if ( text.length() < d->searchLength ) {
        emit error( tr( "Your text is too short to start the search." ) );
        return;
    }
    
    NetworkManager::instance()->getJson( QNetworkRequest( d->requestUrl( text ) ) );
}

#include "SeLogerDistrictQuery.moc"
