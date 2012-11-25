#include "SeLogerCityQuery.h"
#include "NetworkManager.h"
#include "Housing.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QStringList>
#include <QDebug>

class SeLogerCityQueryPrivate : public QObject {
    Q_OBJECT

public:
    SeLogerCityQuery* query;
    int searchLength;

public:
    SeLogerCityQueryPrivate( SeLogerCityQuery* _query )
        : QObject( _query ),
            query( _query ),
            searchLength( 2 )
    {
        connect( NetworkManager::instance(), SIGNAL( jsonFinished( QNetworkReply*, const QByteArray&, const QVariantMap& ) ), this, SLOT( jsonFinished( QNetworkReply*, const QByteArray&, const QVariantMap& ) ) );
        connect( this, SIGNAL( citiesReceived( const City::List& ) ), query, SIGNAL( citiesReceived( const City::List& ) ) );
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
                << "villes"
                << "ville"
                << "suggestions"
            ;
            const QVariantList results = data.value( "json" ).toList();
            QVariantList citiesList;
            bool found = false;
            
            foreach ( const QString& priority, priorities ) {
                foreach ( const QVariant& variant, results ) {
                    const QVariantMap map = variant.toMap();
                    const QString label = map.value( "label" ).toString().toLower();
                    
                    if ( label == priority ) {
                        citiesList = map.value( "values" ).toList();
                        found = true;
                        break;
                    }
                }
                
                if ( found ) {
                    break;
                }
            }
            
            if ( !found ) {
                emit error( SeLogerCityQuery::tr( "No data found." ) );
                return;
            }
            
            City::List cities;
            
            foreach ( const QVariant& cityVariant, citiesList ) {
                const QVariantMap city = cityVariant.toMap();
                
                if ( !city.isEmpty() ) {
                    cities << City( Housing::toPlainText( city.value( "label" ).toString() ), city.value( "value" ).toString(), city.value( "code" ).toString() );
                }
            }
            
            emit citiesReceived( cities );
        }
        else {
            emit error( data.value( "message" ).toString() );
        }
    }

signals:
    void citiesReceived( const City::List& cities );
    void error( const QString& error );
};

SeLogerCityQuery::SeLogerCityQuery( QObject* parent )
    : AbstractCityQuery( parent ),
        d( new SeLogerCityQueryPrivate( this ) )
{
}

SeLogerCityQuery::~SeLogerCityQuery()
{
}

void SeLogerCityQuery::setMinimumSearchLength( int length )
{
    d->searchLength = length;
}

int SeLogerCityQuery::minimumSearchLength() const
{
    return d->searchLength;
}

void SeLogerCityQuery::search( const QString& text )
{
    if ( text.length() < d->searchLength ) {
        emit error( tr( "Your text is too short to start the search." ) );
        return;
    }
    
    NetworkManager::instance()->getJson( QNetworkRequest( d->requestUrl( text ) ) );
}

#include "SeLogerCityQuery.moc"
