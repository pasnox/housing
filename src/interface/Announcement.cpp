#include "Announcement.h"

#include <QSharedData>
#include <QString>
#include <QDateTime>
#include <QDomElement>

class AnnouncementData : public QSharedData
{
public:
    struct Informations {
        QString thumbnail;
        QString title;
        QString label;
        QString description;
    };
    
    struct Pricing {
        int price;
        QString currency;
        QString mention;
        
        Pricing() {
            price = -1;
        }
    };
    
    struct Location {
        int id;
        QString country;
        QString zip;
        QString insee;
        QString city;
        double latitude;
        double longitude;
        QString near;
        QString precision;
        QString dpe;
        
        Location() {
            id = -1;
            latitude = -1.0;
            longitude = -1.0;
        }
    };
    
    struct Contact {
        int id;
        bool audiotel;
        QString name;
        QString siren;
        QString nic;
        
        Contact() {
            id = -1;
            audiotel = false;
        }
    };
    
    struct Details {
        int houseSurface;
        QString surfaceUnite;
        int loungeSurface;
        int year;
        
        Details() {
            houseSurface = -1;
            loungeSurface = -1;
            year = -1;
        }
    };
    
    struct Numbers {
        int rooms;
        int bedrooms;
        int bathrooms;
        int showerrooms;
        int wc;
        int parkings;
        int boxes;
        int terraces;
        
        Numbers() {
            rooms = -1;
            bedrooms = -1;
            bathrooms = -1;
            showerrooms = -1;
            wc = -1;
            parkings = -1;
            boxes = -1;
            terraces = -1;
        }
    };
    
    struct Features {
        bool unused;
        bool exclusive;
        bool star;
        bool terrace;
        bool pool;
        bool lounge;
        
        Features() {
            unused = false;
            exclusive = false;
            star = false;
            terrace = false;
            pool = false;
            lounge = false;
        }
    };
    
    struct Photo {
        typedef QList<Photo> List;
        
        QString url;
        int width;
        int height;
        
        Photo() {
            width = -1;
            height = -1;
        }
    };
    
    // announe
    int id;
    QString url;
    QDateTime created;
    QDateTime updated;
    Informations informations;
    Pricing pricing;
    Location location;
    Contact contact;
    Details details;
    Numbers numbers;
    Features features;
    Photo::List photos;

public:
    AnnouncementData() {
    }
    
    AnnouncementData( const AnnouncementData& other )
        : QSharedData( other ),
            id( -1 )
    {
    }
    
    ~AnnouncementData() {
    }
};

Announcement::Announcement( const QVariant& variant )
    : d( new AnnouncementData )
{
    if ( !variant.isNull() ) {
        fromVariant( variant );
    }
}

Announcement::Announcement( const QDomElement& _element )
    : d( new AnnouncementData )
{
    if ( _element.isNull() || _element.tagName().toLower() != "announcement" ) {
        return;
    }
    
    QDomElement element = _element;
    
    // announe
    d->id = element.attribute( "id", "-1" ).toInt();
    d->url = element.attribute( "url" );
    d->created = QDateTime::fromString( element.attribute( "created" ), Qt::ISODate );
    d->updated = QDateTime::fromString( element.attribute( "updated" ), Qt::ISODate );
    
    // informations
    element = _element.firstChildElement( "informations" );
    d->informations.thumbnail = element.attribute( "thumbnail" );
    d->informations.title = element.attribute( "title" );
    d->informations.label = element.attribute( "label" );
    d->informations.description = element.attribute( "description" );
    
    // pricing
    element = _element.firstChildElement( "pricing" );
    d->pricing.price = element.attribute( "price" ).toDouble();
    d->pricing.currency = element.attribute( "currency" );
    d->pricing.mention = element.attribute( "mention" );
    
    // location
    element = _element.firstChildElement( "location" );
    d->location.id = element.attribute( "id" ).toInt();
    d->location.country = element.attribute( "country" );
    d->location.zip = element.attribute( "zip" );
    d->location.insee = element.attribute( "insee" );
    d->location.city = element.attribute( "city" );
    d->location.latitude = element.attribute( "latitude" ).toDouble();
    d->location.longitude = element.attribute( "longitude" ).toDouble();
    d->location.near = element.attribute( "near" );
    d->location.precision = element.attribute( "precision" );
    d->location.dpe = element.attribute( "dpe" );
    
    // contact
    element = _element.firstChildElement( "contact" );
    d->contact.id = element.attribute( "id" ).toInt();
    d->contact.audiotel = QVariant( element.attribute( "audiotel" ) ).toBool();
    d->contact.name = element.attribute( "name" );
    d->contact.siren = element.attribute( "siren" );
    d->contact.nic = element.attribute( "nic" );
    
    // details
    element = _element.firstChildElement( "details" );
    d->details.houseSurface = element.attribute( "houseSurface" ).toInt();
    d->details.surfaceUnite = element.attribute( "surfaceUnite" );
    d->details.loungeSurface = element.attribute( "loungeSurface" ).toInt();
    d->details.year = element.attribute( "year" ).toInt();
    
    // numbers
    element = _element.firstChildElement( "numbers" );
    d->numbers.rooms = element.attribute( "rooms" ).toInt();
    d->numbers.bedrooms = element.attribute( "bedrooms" ).toInt();
    d->numbers.bathrooms = element.attribute( "bathrooms" ).toInt();
    d->numbers.showerrooms = element.attribute( "showerrooms" ).toInt();
    d->numbers.wc = element.attribute( "wc" ).toInt();
    d->numbers.parkings = element.attribute( "parkings" ).toInt();
    d->numbers.boxes = element.attribute( "boxes" ).toInt();
    d->numbers.terraces = element.attribute( "terraces" ).toInt();
    
    // features
    element = _element.firstChildElement( "features" );
    d->features.unused = QVariant( element.attribute( "country" ) ).toBool();
    d->features.exclusive = QVariant( element.attribute( "country" ) ).toBool();
    d->features.star = QVariant( element.attribute( "country" ) ).toBool();
    d->features.terrace = QVariant( element.attribute( "country" ) ).toBool();
    d->features.pool = QVariant( element.attribute( "country" ) ).toBool();
    d->features.lounge = QVariant( element.attribute( "country" ) ).toBool();
    
    // photos
    const QDomNodeList photosNodes = _element.elementsByTagName( "photo" );
    
    for ( int i = 0; i < photosNodes.count(); i++ ) {
        const QDomElement photoNode = photosNodes.at( i ).toElement();
        AnnouncementData::Photo photo;
        
        photo.url = photoNode.attribute( "country" );
        photo.width = photoNode.attribute( "country" ).toInt();
        photo.height = photoNode.attribute( "country" ).toInt();
        
        d->photos << photo;
    }
}

Announcement::Announcement( const Announcement& other )
    : d( other.d )
{
}

Announcement::~Announcement()
{
}

Announcement::operator QVariant()
{
    return QVariant::fromValue( *this );
}

Announcement::operator QVariant() const
{
    return QVariant::fromValue( *this );
}

bool Announcement::operator==( const Announcement& other ) const
{
    return d->id == other.d->id;
}

bool Announcement::isNull() const
{
    return d->id == -1;
}

int Announcement::id() const
{
    return d->id;
}

QString Announcement::url() const
{
    return d->url;
}

QDateTime Announcement::created() const
{
    return d->created;
}

QDateTime Announcement::updated() const
{
    return d->updated;
}

QString Announcement::thumbnailInformations() const
{
    return d->informations.thumbnail;
}

QString Announcement::titleInformations() const
{
    return d->informations.title;
}

QString Announcement::labelInformations() const
{
    return d->informations.label;
}

QString Announcement::descriptionInformations() const
{
    return d->informations.description;
}

int Announcement::pricePricing() const
{
    return d->pricing.price;
}

QString Announcement::currencyPricing() const
{
    return d->pricing.currency;
}

QString Announcement::mentionPricing() const
{
    return d->pricing.mention;
}

int Announcement::idLocation() const
{
    return d->location.id;
}

QString Announcement::countryLocation() const
{
    return d->location.country;
}

QString Announcement::zipLocation() const
{
    return d->location.zip;
}

QString Announcement::inseeLocation() const
{
    return d->location.insee;
}

QString Announcement::cityLocation() const
{
    return d->location.city;
}

double Announcement::latitudeLocation() const
{
    return d->location.latitude;
}

double Announcement::longitudeLocation() const
{
    return d->location.longitude;
}

QString Announcement::nearLocation() const
{
    return d->location.near;
}

QString Announcement::precisionLocation() const
{
    return d->location.precision;
}

QString Announcement::dpeLocation() const
{
    return d->location.dpe;
}

int Announcement::idContact() const
{
    return d->contact.id;
}

bool Announcement::audiotelContact() const
{
    return d->contact.audiotel;
}

QString Announcement::nameContact() const
{
    return d->contact.name;
}

QString Announcement::sirenContact() const
{
    return d->contact.siren;
}

QString Announcement::nicContact() const
{
    return d->contact.nic;
}

int Announcement::houseSurfaceDetails() const
{
    return d->details.houseSurface;
}

QString Announcement::surfaceUniteDetails() const
{
    return d->details.surfaceUnite;
}

int Announcement::loungeSurfaceDetails() const
{
    return d->details.loungeSurface;
}

int Announcement::yearDetails() const
{
    return d->details.year;
}

int Announcement::roomsNumbers() const
{
    return d->numbers.rooms;
}

int Announcement::bedroomsNumbers() const
{
    return d->numbers.bedrooms;
}

int Announcement::bathroomsNumbers() const
{
    return d->numbers.bathrooms;
}

int Announcement::showerroomsNumbers() const
{
    return d->numbers.showerrooms;
}

int Announcement::wcNumbers() const
{
    return d->numbers.wc;
}

int Announcement::parkingsNumbers() const
{
    return d->numbers.parkings;
}

int Announcement::boxesNumbers() const
{
    return d->numbers.boxes;
}

int Announcement::terracesNumbers() const
{
    return d->numbers.terraces;
}

bool Announcement::unusedFeatures() const
{
    return d->features.unused;
}

bool Announcement::exclusiveFeatures() const
{
    return d->features.exclusive;
}

bool Announcement::starFeatures() const
{
    return d->features.star;
}

bool Announcement::terraceFeatures() const
{
    return d->features.terrace;
}

bool Announcement::poolFeatures() const
{
    return d->features.pool;
}

bool Announcement::loungeFeatures() const
{
    return d->features.lounge;
}

int Announcement::countPhoto() const
{
    return d->photos.count();
}

QString Announcement::urlPhoto( int index ) const
{
    return d->photos.value( index ).url;
}

QSize Announcement::sizePhoto( int index ) const
{
    return QSize( d->photos.value( index ).width, d->photos.value( index ).height );
}

QVariant Announcement::toVariant() const
{
    QVariantMap map;
    /*map[ "label" ] = d->label;
    map[ "value" ] = d->value;
    map[ "code" ] = d->code;*/
    return map;
}

void Announcement::fromVariant( const QVariant& variant )
{
    if ( !variant.type() == QVariant::Map ) {
        return;
    }
    
    const QVariantMap map = variant.toMap();
    /*d->label = map.value( "label" ).toString();
    d->value = map.value( "value" ).toString();
    d->code = map.value( "code" ).toString();*/
}

QVariant Announcement::listToVariant( const Announcement::List& announces )
{
    QVariantList list;
    
    foreach ( const Announcement& announce, announces ) {
        list << announce.toVariant();
    }
    
    return list;
}

Announcement::List Announcement::variantToList( const QVariant& variant )
{
    Announcement::List list;
    
    if ( variant.type() == QVariant::List ) {
        const QVariantList announces = variant.toList();
        
        foreach ( const QVariant& announce, announces ) {
            list << Announcement( announce );
        }
    }
    
    return list;
}
