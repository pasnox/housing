#ifndef ABSTRACTHOUSINGDRIVER_H
#define ABSTRACTHOUSINGDRIVER_H

#include <QObject>
#include <QNetworkRequest>
#include <QByteArray>
#include <QHash>
#include <QMap>
#include <QVariant>
#include <QMetaType>
#include <QSet>

#include "Announcement.h"
#include "City.h"

class AbstractCityQuery;

class AbstractHousingDriver : public QObject
{
    Q_OBJECT
    
public:
    // kind of search
    enum SearchType {
        SearchTypeRent = 0x1, // can search for renting
        SearchTypePurchase = 0x2, // can search for purchase
        SearchTypeAll = SearchTypeRent | SearchTypePurchase // can search both purchase and renting
    };
    
    // kind of sorting
    enum SearchSortingFlag {
        SearchSortingNone = 0x0, // can not sort
        SearchSortingAscendingDate = 0x1, // can sort by ascending date
        SearchSortingDescendingDate = 0x2, // can sort by descending date
        SearchSortingAscendingPrice = 0x4, // can sort by ascending price
        SearchSortingDescendingPrice = 0x8, // can sort by descending price
        SearchSortingAscendingSurface = 0x10, // can sort by ascending surface
        SearchSortingDescendingSurface = 0x20, // can sort by descending surface
        SearchSortingAll =
            SearchSortingAscendingDate | SearchSortingDescendingDate |
            SearchSortingAscendingPrice | SearchSortingDescendingPrice |
            SearchSortingAscendingSurface | SearchSortingDescendingSurface
    };
    
    // kind of looked property
    enum SearchProperty {
        SearchPropertyNone = 0x0, // no property
        SearchPropertyApartment = 0x1, // look for an apartment
        SearchPropertyHouseOrVilla = 0x2, // look for a house or villa
        SearchPropertyParkingOrBox = 0x4, // look for a parking or a box
        SearchPropertyGround = 0x8, // look for a ground/terrain
        SearchPropertyShop = 0x10, // look for a shop
        SearchPropertyCommercialLocal = 0x20, // look for a commercial local
        SearchPropertyOffices = 0x40, // look for offices
        SearchPropertyLoftOrWorkshopOrSurface = 0x80, // look for a loft, workshop or surface
        SearchPropertyTenement = 0x100, // look for a tenement
        SearchPropertyBuilding = 0x200, // look for a building
        SearchPropertyCastle = 0x400, // look for a castle
        SearchPropertyMansion = 0x800, // look for a mansion
        SearchPropertyOthers = 0x1000, // lookf for something others
        SearchPropertyAll =
            SearchPropertyApartment | SearchPropertyHouseOrVilla | SearchPropertyParkingOrBox |
            SearchPropertyGround | SearchPropertyShop | SearchPropertyCommercialLocal |
            SearchPropertyOffices | SearchPropertyLoftOrWorkshopOrSurface | SearchPropertyTenement |
            SearchPropertyBuilding | SearchPropertyCastle | SearchPropertyMansion | SearchPropertyOthers
    };
    
    enum SearchInput {
        SearchInputNumberOfRooms = 0x1, // number of rooms
        SearchInputNumberOfBedrooms = 0x2, // number of bedrooms
        SearchInputMinimumBudget = 0x4, // minimum budget
        SearchInputMaximumBudget = 0x8, // maximum budget
        SearchInputMinimumSurface = 0x10, // minimum surface
        SearchInputMaximumSurface = 0x20, // maximum surface
        SearchInputMinimumGround = 0x40, // minimum ground
        SearchInputMaximumGround = 0x80, // maximum ground
        SearchInputAll =
            SearchInputNumberOfRooms | SearchInputNumberOfBedrooms | SearchInputMinimumBudget |
            SearchInputMaximumBudget | SearchInputMinimumSurface | SearchInputMaximumSurface |
            SearchInputMinimumGround | SearchInputMaximumGround
    };
    
    enum SearchFeature {
        SearchFeatureNone = 0x0, // no property feature
        SearchFeatureElevator = 0x1, // property has elevator
        SearchFeatureDigicode = 0x2, // property has digicode
        SearchFeatureIntercom = 0x4, // property has intercom
        SearchFeatureCaretaker = 0x8, // property has caretaker/concierge
        SearchFeaturePool = 0x10, // property has pool
        SearchFeatureTerrace = 0x20, // property has terrace
        SearchFeatureBalcony = 0x40, // property has balcony
        SearchFeatureParking = 0x80, // property has parking
        SearchFeatureBox = 0x100, // property has box
        SearchFeatureCellar = 0x200, // property has cellar
        SearchFeatureAll =
            SearchFeatureElevator | SearchFeatureDigicode | SearchFeatureIntercom |
            SearchFeatureCaretaker | SearchFeaturePool | SearchFeatureTerrace |
            SearchFeatureBalcony | SearchFeatureParking | SearchFeatureBox |
            SearchFeatureCellar
    };
    
    Q_DECLARE_FLAGS( SearchTypes, SearchType )
    Q_DECLARE_FLAGS( SearchSorting, SearchSortingFlag )
    Q_DECLARE_FLAGS( SearchProperties, SearchProperty )
    Q_DECLARE_FLAGS( SearchInputs, SearchInput )
    Q_DECLARE_FLAGS( SearchFeatures, SearchFeature )
    
    struct RequestProperties {
        SearchType type;
        SearchSortingFlag sorting;
        SearchProperties properties;
        SearchFeatures features;
        QHash<SearchInput, QVariant> inputs;
        City::List cities;
        QSet<int> ignoredIdSet;
        QSet<int> bookmarkedIdSet;
        
        RequestProperties( const QVariant& variant = QVariant() );
        
        QVariant toVariant() const;
        void fromVariant( const QVariant& variant );
        
        // helpers
        void setType( int value );
        void setSorting( int value );
        void setProperties( int value );
        void setFeatures( int value );
        
        void setNumberOfRooms( const QVariantList& values );
        QVariantList numberOfRooms() const;
        
        void setNumberOfBedrooms( const QVariantList& values );
        QVariantList numberOfBedrooms() const;
        
        void setMinimumBudget( int value );
        int minimumBudget() const;
        
        void setMaximumBudget( int value );
        int maximumBudget() const;
        
        void setMinimumSurface( int value );
        int minimumSurface() const;
        
        void setMaximumSurface( int value );
        int maximumSurface() const;
        
        void setMinimumGround( int value );
        int minimumGround() const;
        
        void setMaximumGround( int value );
        int maximumGround() const;
    };
    
    typedef QList<AbstractHousingDriver*> List;
    
    AbstractHousingDriver( QObject* parent = 0 );
    virtual ~AbstractHousingDriver();
    
    virtual operator QVariant();
    
    bool isSupportedSearchType( AbstractHousingDriver::SearchType flag ) const;
    bool isSupportedSearchSortingFlag( AbstractHousingDriver::SearchSortingFlag flag ) const;
    bool isSupportedSearchProperty( AbstractHousingDriver::SearchProperty flag ) const;
    bool isSupportedSearchInput( AbstractHousingDriver::SearchInput flag ) const;
    bool isSupportedSearchFeature( AbstractHousingDriver::SearchFeature flag ) const;
    
    virtual QString name() const = 0;
    
    virtual AbstractHousingDriver::SearchTypes supportedSearchTypes() const = 0;
    virtual AbstractHousingDriver::SearchSorting supportedSearchSorting() const = 0;
    virtual AbstractHousingDriver::SearchProperties supportedSearchProperties() const = 0;
    virtual AbstractHousingDriver::SearchInputs supportedSearchInputs() const = 0;
    virtual AbstractHousingDriver::SearchFeatures supportedSearchFeatures() const = 0;
    
    virtual AbstractCityQuery* cityQuery() const = 0;
    virtual QMap<QString, QString> roomsInputs() const = 0;
    virtual QMap<QString, QString> bedroomsInputs() const = 0;
    virtual bool isOwnUrl( const QUrl& url ) const = 0;
    virtual QByteArray testCase() const = 0;
    virtual QString xPathQuery() const = 0;
    virtual void setUpSearchRequest( QNetworkRequest& request, QByteArray& data, const AbstractHousingDriver::RequestProperties& properties ) const = 0;
    virtual bool parseSearchRequestData( const QByteArray& data, Announcement::List& announcements, QString* error = 0 ) const = 0;
    virtual bool canFetchMore() const = 0;
    
    static void registerDriver( AbstractHousingDriver* driver );
    static AbstractHousingDriver::List registeredDrivers();

protected:
    bool parseStandardDomDocument( const QString& xml, Announcement::List& announcements, QString* error = 0 ) const;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( AbstractHousingDriver::SearchTypes )
Q_DECLARE_OPERATORS_FOR_FLAGS( AbstractHousingDriver::SearchSorting )
Q_DECLARE_OPERATORS_FOR_FLAGS( AbstractHousingDriver::SearchProperties )
Q_DECLARE_OPERATORS_FOR_FLAGS( AbstractHousingDriver::SearchInputs )
Q_DECLARE_OPERATORS_FOR_FLAGS( AbstractHousingDriver::SearchFeatures )

Q_DECLARE_METATYPE( AbstractHousingDriver* )

#endif // ABSTRACTHOUSINGDRIVER_H
