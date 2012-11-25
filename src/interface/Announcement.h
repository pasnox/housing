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
