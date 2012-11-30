#include "AbstractHousingDriver.h"

#include <QDomDocument>
#include <QDebug>

class AbstractHousingDriverPrivate {
public:
    QHash<const QMetaObject*, AbstractHousingDriver*> drivers;

public:
    ~AbstractHousingDriverPrivate() {
        qDeleteAll( drivers.values() );
        drivers.clear();
    }
};

static AbstractHousingDriverPrivate mRegisteredDrivers;

AbstractHousingDriver::RequestProperties::RequestProperties( const QVariant& variant )
{
    if ( !variant.isNull() ) {
        fromVariant( variant );
    }
}

QVariant AbstractHousingDriver::RequestProperties::toVariant() const
{
    QVariantMap variantInputs;
    QVariantList variantIgnored;
    QVariantList variantBookmarked;
    QVariantMap map;
    
    foreach ( const AbstractHousingDriver::SearchInput& input, inputs.keys() ) {
        variantInputs[ QString::number( input ) ] = inputs[ input ];
    }
    
    foreach ( const int& id, ignoredIdSet ) {
        variantIgnored << QString::number( id );
    }
    
    foreach ( const int& id, bookmarkedIdSet ) {
        variantBookmarked << QString::number( id );
    }
    
    map[ "type" ] = int( type );
    map[ "sorting" ] = int( sorting );
    map[ "properties" ] = int( properties );
    map[ "features" ] = int( features );
    map[ "inputs" ] = variantInputs;
    map[ "cities" ] = City::listToVariant( cities );
    map[ "ignored" ] = variantIgnored;
    map[ "bookmarked" ] = variantBookmarked;
    
    return map;
}

void AbstractHousingDriver::RequestProperties::fromVariant( const QVariant& variant )
{
    if ( !variant.type() == QVariant::Map ) {
        return;
    }
    
    const QVariantMap map = variant.toMap();
    const QVariantMap variantInputs = map.value( "inputs" ).toMap();
    const QVariantList variantIgnored = map.value( "ignored" ).toList();
    const QVariantList variantBookmarked = map.value( "bookmarked" ).toList();
    
    type = SearchType( map.value( "type" ).toInt() );
    sorting = SearchSortingFlag( map.value( "sorting" ).toInt() );
    properties = SearchProperties( map.value( "properties" ).toInt() );
    features = SearchFeatures( map.value( "features" ).toInt() );
    
    inputs.clear();
    
    foreach ( const QString& input, variantInputs.keys() ) {
        inputs[ AbstractHousingDriver::SearchInput( input.toInt() ) ] = variantInputs[ input ];
    }
    
    cities = City::variantToList( map.value( "cities" ) );
    
    ignoredIdSet.clear();
    
    foreach ( const QVariant& id, variantIgnored ) {
        ignoredIdSet << id.toInt();
    }
    
    bookmarkedIdSet.clear();
    
    foreach ( const QVariant& id, variantBookmarked ) {
        bookmarkedIdSet << id.toInt();
    }
}

void AbstractHousingDriver::RequestProperties::setType( int value )
{
    type = AbstractHousingDriver::SearchType( value );
}

void AbstractHousingDriver::RequestProperties::setSorting( int value )
{
    sorting = AbstractHousingDriver::SearchSortingFlag( value );
}

void AbstractHousingDriver::RequestProperties::setProperties( int value )
{
    properties = AbstractHousingDriver::SearchProperties( value );
}

void AbstractHousingDriver::RequestProperties::setFeatures( int value )
{
    features = AbstractHousingDriver::SearchFeatures( value );
}

void AbstractHousingDriver::RequestProperties::setNumberOfRooms( const QVariantList& values )
{
    inputs[ AbstractHousingDriver::SearchInputNumberOfRooms ] = values;
}

QVariantList AbstractHousingDriver::RequestProperties::numberOfRooms() const
{
    return inputs.value( AbstractHousingDriver::SearchInputNumberOfRooms ).toList();
}

void AbstractHousingDriver::RequestProperties::setNumberOfBedrooms( const QVariantList& values )
{
    inputs[ AbstractHousingDriver::SearchInputNumberOfBedrooms ] = values;
}

QVariantList AbstractHousingDriver::RequestProperties::numberOfBedrooms() const
{
    return inputs.value( AbstractHousingDriver::SearchInputNumberOfBedrooms ).toList();
}

void AbstractHousingDriver::RequestProperties::setMinimumBudget( int value )
{
    inputs[ AbstractHousingDriver::SearchInputMinimumBudget ] = value;
}

int AbstractHousingDriver::RequestProperties::minimumBudget() const
{
    return inputs.value( AbstractHousingDriver::SearchInputMinimumBudget ).toInt();
}

void AbstractHousingDriver::RequestProperties::setMaximumBudget( int value )
{
    inputs[ AbstractHousingDriver::SearchInputMaximumBudget ] = value;
}

int AbstractHousingDriver::RequestProperties::maximumBudget() const
{
    return inputs.value( AbstractHousingDriver::SearchInputMaximumBudget ).toInt();
}

void AbstractHousingDriver::RequestProperties::setMinimumSurface( int value ) 
{
    inputs[ AbstractHousingDriver::SearchInputMinimumSurface ] = value;
}

int AbstractHousingDriver::RequestProperties::minimumSurface() const
{
    return inputs.value( AbstractHousingDriver::SearchInputMinimumSurface ).toInt();
}

void AbstractHousingDriver::RequestProperties::setMaximumSurface( int value )
{
    inputs[ AbstractHousingDriver::SearchInputMaximumSurface ] = value;
}

int AbstractHousingDriver::RequestProperties::maximumSurface() const
{
    return inputs.value( AbstractHousingDriver::SearchInputMaximumSurface ).toInt();
}

void AbstractHousingDriver::RequestProperties::setMinimumGround( int value )
{
    inputs[ AbstractHousingDriver::SearchInputMinimumGround ] = value;
}

int AbstractHousingDriver::RequestProperties::minimumGround() const
{
    return inputs.value( AbstractHousingDriver::SearchInputMinimumGround ).toInt();
}

void AbstractHousingDriver::RequestProperties::setMaximumGround( int value )
{
    inputs[ AbstractHousingDriver::SearchInputMaximumGround ] = value;
}

int AbstractHousingDriver::RequestProperties::maximumGround() const
{
    return inputs.value( AbstractHousingDriver::SearchInputMaximumGround ).toInt();
}

AbstractHousingDriver::RequestResultProperties::RequestResultProperties()
    : page( -1 ),
        totalPage( -1 ),
        found( -1 ),
        visible( -1 ),
        hasNextPage( false )
{
}

AbstractHousingDriver::AbstractHousingDriver( QObject* parent )
    : QObject( parent )
{
}

AbstractHousingDriver::~AbstractHousingDriver()
{
}

AbstractHousingDriver::operator QVariant()
{
    return QVariant::fromValue( this );
}

bool AbstractHousingDriver::isSupportedSearchType( AbstractHousingDriver::SearchType flag ) const
{
    return ( supportedSearchTypes() & flag ) != 0;
}

bool AbstractHousingDriver::isSupportedSearchSortingFlag( AbstractHousingDriver::SearchSortingFlag flag ) const
{
    return ( supportedSearchSorting() & flag ) != 0;
}

bool AbstractHousingDriver::isSupportedSearchProperty( AbstractHousingDriver::SearchProperty flag ) const
{
    return ( supportedSearchProperties() & flag ) != 0;
}

bool AbstractHousingDriver::isSupportedSearchInput( AbstractHousingDriver::SearchInput flag ) const
{
    return ( supportedSearchInputs() & flag ) != 0;
}

bool AbstractHousingDriver::isSupportedSearchFeature( AbstractHousingDriver::SearchFeature flag ) const
{
    return ( supportedSearchFeatures() & flag ) != 0;
}

void AbstractHousingDriver::registerDriver( AbstractHousingDriver* driver )
{
    if ( !mRegisteredDrivers.drivers.contains( &driver->staticMetaObject ) ) {
        mRegisteredDrivers.drivers[ &driver->staticMetaObject ] = driver;
    }
}

AbstractHousingDriver::List AbstractHousingDriver::registeredDrivers()
{
    return mRegisteredDrivers.drivers.values();
}

bool AbstractHousingDriver::parseStandardDomDocument( const QString& xml, Announcement::List& announcements, RequestResultProperties* properties ) const
{
    QDomDocument document;
    int errorLine;
    int errorColumn;
    
    if ( !document.setContent( xml, properties ? &properties->error : 0, &errorLine, &errorColumn ) ) {
        return false;
    }
    
    const QDomElement root = document.documentElement();
    const QDomNodeList nodes = document.elementsByTagName( "announcement" );
    
    if ( properties ) {
        properties->page = qMax( root.attribute( "page", "0" ).toInt(), 1 );
        properties->totalPage = qMax( root.attribute( "totalPage", "0" ).toInt(), 1 );
        properties->found = root.attribute( "found", "0" ).toInt();
        properties->visible = root.attribute( "visible", "0" ).toInt();
        properties->hasNextPage = properties->totalPage > properties->page;
    }
    
    for ( int i = 0; i < nodes.count(); i++ ) {
        const Announcement announcement( nodes.at( i ).toElement() );
        
        if ( !announcement.isNull() ) {
            announcements << announcement;
        }
    }

    return true;
}
