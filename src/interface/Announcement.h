/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : Announcement.h
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
#ifndef ANNOUNCEMENT_H
#define ANNOUNCEMENT_H

#include <QSharedDataPointer>
#include <QList>
#include <QVariant>
#include <QSize>
#include <QDateTime>

class AnnouncementData;
class QDomElement;

class Announcement
{
public:
    typedef QList<Announcement> List;
    
    Announcement( const QVariant& variant = QVariant() );
    Announcement( const QDomElement& element );
    Announcement( const Announcement& other );
    virtual ~Announcement();
    
    virtual operator QVariant();
    virtual operator QVariant() const;
    virtual Announcement& operator=( const Announcement& other );
    virtual bool operator==( const Announcement& other ) const;
    
    bool isNull() const;
    
    int id() const;
    QString url() const;
    QDateTime created() const;
    QDateTime updated() const;

    QString thumbnailInformations() const;
    QString titleInformations() const;
    QString labelInformations() const;
    QString descriptionInformations() const;

    int pricePricing() const;
    QString currencyPricing() const;
    QString mentionPricing() const;

    int idLocation() const;
    QString countryLocation() const;
    QString zipLocation() const;
    QString inseeLocation() const;
    QString cityLocation() const;
    double latitudeLocation() const;
    double longitudeLocation() const;
    QString nearLocation() const;
    QString precisionLocation() const;
    QString dpeLocation() const;

    int idContact() const;
    bool audiotelContact() const;
    QString nameContact() const;
    QString sirenContact() const;
    QString nicContact() const;

    int houseSurfaceDetails() const;
    QString surfaceUniteDetails() const;
    int loungeSurfaceDetails() const;
    int yearDetails() const;

    int roomsNumbers() const;
    int bedroomsNumbers() const;
    int bathroomsNumbers() const;
    int showerroomsNumbers() const;
    int wcNumbers() const;
    int parkingsNumbers() const;
    int boxesNumbers() const;
    int terracesNumbers() const;

    bool unusedFeatures() const;
    bool exclusiveFeatures() const;
    bool starFeatures() const;
    bool terraceFeatures() const;
    bool poolFeatures() const;
    bool loungeFeatures() const;

    int countPhoto() const;
    QString urlPhoto( int index ) const;
    QSize sizePhoto( int index ) const;

    QVariant toVariant() const;
    void fromVariant( const QVariant& variant );

    static QVariant listToVariant( const Announcement::List& announces );
    static Announcement::List variantToList( const QVariant& variant );

private:
    QSharedDataPointer<AnnouncementData> d;
};

Q_DECLARE_METATYPE( Announcement )

#endif // ANNOUNCEMENT_H
