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
