/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : Feedback.h
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
