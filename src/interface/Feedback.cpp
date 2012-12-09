#include "Feedback.h"
#include "objects/Housing.h"

#include <QSharedData>
#include <QDateTime>
#include <QDebug>

class FeedbackPrivate : public QSharedData
{
public:
    QDateTime dateTime;
    QString message;

public:
    FeedbackPrivate()
        : dateTime( QDateTime::currentDateTimeUtc() )
    {
    }
    
    FeedbackPrivate( const FeedbackPrivate& other )
        : QSharedData( other ),
            dateTime( other.dateTime ),
            message( other.message )
    {
    }
    
    ~FeedbackPrivate() {
    }
};

Feedback::Feedback( const QVariant& variant )
    : d( 0 )
{
    operator=( variant );
}

Feedback::Feedback( const QDateTime& dateTime, const QString& message )
    : d( new FeedbackPrivate )
{
    d->dateTime = dateTime;
    d->message = message;
}

Feedback::Feedback( const Feedback& other )
    : d( other.d )
{
}

Feedback::~Feedback()
{
}

Feedback& Feedback::operator=( const Feedback& other )
{
    if ( this != &other ) {
        d = other.d;
    }
    
    return *this;
}

bool Feedback::operator==( const Feedback& other ) const
{
    return d == other.d ||
        ( d->dateTime == other.d->dateTime && d->message == other.d->message )
    ;
}

bool Feedback::operator<( const Feedback& other ) const
{
    return d->dateTime < other.d->dateTime;
}

Feedback::operator QVariant() const
{
    QVariantMap map;
    map[ "dateTime" ] = d->dateTime;
    map[ "message" ] = d->message;
    return map;
}

Feedback& Feedback::operator=( const QVariant& variant )
{
    if ( variant.canConvert<Feedback>() ) {
        d = variant.value<Feedback>().d;
    }
    else {
        if ( !d ) {
            d = new FeedbackPrivate;
        }
        
        if ( variant.type() == QVariant::Map ) {
            const QVariantMap map = variant.toMap();
            d->dateTime = map.value( "dateTime" ).toDateTime();
            d->message = map.value( "message" ).toString();
        }
    }
   
   return *this;
}

bool Feedback::operator==( const QVariant& variant ) const
{
    return operator==( Feedback( variant ) );
}

bool Feedback::operator<( const QVariant& variant ) const
{
    return operator<( Feedback( variant ) );
}

bool Feedback::isNull() const
{
    return !d || ( d->dateTime.isNull() && d->message.isNull() );
}

void Feedback::setDateTime( const QDateTime& dateTime )
{
    d->dateTime = dateTime;
}

QDateTime Feedback::dateTime() const
{
    return d->dateTime;
}

void Feedback::setMessage( const QString& message )
{
    d->message = message;
}

QString Feedback::message() const
{
    return d->message;
}

QVariantList Feedback::listToVariantList( const Feedback::List& feedbackList )
{
    QVariantList list;
    
    foreach ( const Feedback& feedback, feedbackList ) {
        list << feedback;
    }
    
    return list;
}

Feedback::List Feedback::variantListToList( const QVariantList& variantList )
{
    Feedback::List list;
    
    foreach ( const QVariant& variant, variantList ) {
        const Feedback feedback( variant );
        
        if ( !feedback.isNull() ) {
            list << variant;
        }
    }
    
    return list;
}
