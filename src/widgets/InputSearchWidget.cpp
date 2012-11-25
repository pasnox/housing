#include "InputSearchWidget.h"
#include "ui_InputSearchWidget.h"
#include "Housing.h"

#include <QEvent>
#include <QDebug>

class InputSearchWidgetPrivate : public QObject {
    Q_OBJECT

public:
    InputSearchWidget* widget;
    Ui_InputSearchWidget* ui;
    QSet<int> ignoredIdSet;
    QSet<int> bookmarkedIdSet;
    
public:
    InputSearchWidgetPrivate( InputSearchWidget* _widget )
        : QObject( _widget ),
            widget( _widget ),
            ui( new Ui_InputSearchWidget )
    {
        ui->setupUi( widget );
        
        // TODO: replace with a Fresh pCheckComboBox when possible
        ui->cbProperties->addItem( tr( "None" ), AbstractHousingDriver::SearchPropertyNone );
        ui->cbProperties->addItem( tr( "Apartment" ), AbstractHousingDriver::SearchPropertyApartment );
        ui->cbProperties->addItem( tr( "House / Villa" ), AbstractHousingDriver::SearchPropertyHouseOrVilla );
        ui->cbProperties->addItem( tr( "Parking / Box" ), AbstractHousingDriver::SearchPropertyParkingOrBox );
        ui->cbProperties->addItem( tr( "Ground" ), AbstractHousingDriver::SearchPropertyGround );
        ui->cbProperties->addItem( tr( "Shop" ), AbstractHousingDriver::SearchPropertyShop );
        ui->cbProperties->addItem( tr( "Commercial Local" ), AbstractHousingDriver::SearchPropertyCommercialLocal );
        ui->cbProperties->addItem( tr( "Offices" ), AbstractHousingDriver::SearchPropertyOffices );
        ui->cbProperties->addItem( tr( "Loft / Workshop / Surface" ), AbstractHousingDriver::SearchPropertyLoftOrWorkshopOrSurface );
        ui->cbProperties->addItem( tr( "Tenement" ), AbstractHousingDriver::SearchPropertyTenement );
        ui->cbProperties->addItem( tr( "Building" ), AbstractHousingDriver::SearchPropertyBuilding );
        ui->cbProperties->addItem( tr( "Castle" ), AbstractHousingDriver::SearchPropertyCastle );
        ui->cbProperties->addItem( tr( "Mansion" ), AbstractHousingDriver::SearchPropertyMansion );
        ui->cbProperties->addItem( tr( "Others" ), AbstractHousingDriver::SearchPropertyOthers );
        ui->cbProperties->addItem( tr( "All" ), AbstractHousingDriver::SearchPropertyAll );
        
        // TODO: replace with a Fresh pCheckComboBox when possible
        ui->cbSorting->addItem( tr( "None" ), AbstractHousingDriver::SearchSortingNone );
        ui->cbSorting->addItem( tr( "Ascending date" ), AbstractHousingDriver::SearchSortingAscendingDate );
        ui->cbSorting->addItem( tr( "Descending date" ), AbstractHousingDriver::SearchSortingDescendingDate );
        ui->cbSorting->addItem( tr( "Ascending price" ), AbstractHousingDriver::SearchSortingAscendingPrice );
        ui->cbSorting->addItem( tr( "Descending price" ), AbstractHousingDriver::SearchSortingDescendingPrice );
        ui->cbSorting->addItem( tr( "Ascending surface" ), AbstractHousingDriver::SearchSortingAscendingSurface );
        ui->cbSorting->addItem( tr( "Descending surface" ), AbstractHousingDriver::SearchSortingDescendingSurface );
        
        // TODO: replace with a Fresh pCheckComboBox when possible
        ui->cbFeatures->addItem( tr( "None" ), AbstractHousingDriver::SearchFeatureNone );
        ui->cbFeatures->addItem( tr( "Elevator" ), AbstractHousingDriver::SearchFeatureElevator );
        ui->cbFeatures->addItem( tr( "Digicode" ), AbstractHousingDriver::SearchFeatureDigicode );
        ui->cbFeatures->addItem( tr( "Intercom" ), AbstractHousingDriver::SearchFeatureIntercom );
        ui->cbFeatures->addItem( tr( "Caretaker" ), AbstractHousingDriver::SearchFeatureCaretaker );
        ui->cbFeatures->addItem( tr( "Pool" ), AbstractHousingDriver::SearchFeaturePool );
        ui->cbFeatures->addItem( tr( "Terrace" ), AbstractHousingDriver::SearchFeatureTerrace );
        ui->cbFeatures->addItem( tr( "Balcony" ), AbstractHousingDriver::SearchFeatureBalcony );
        ui->cbFeatures->addItem( tr( "Parking" ), AbstractHousingDriver::SearchFeatureParking );
        ui->cbFeatures->addItem( tr( "Box" ), AbstractHousingDriver::SearchFeatureBox );
        ui->cbFeatures->addItem( tr( "Cellar" ), AbstractHousingDriver::SearchFeatureCellar );
        ui->cbFeatures->addItem( tr( "All" ), AbstractHousingDriver::SearchFeatureAll );
        
        foreach ( AbstractHousingDriver* driver, AbstractHousingDriver::registeredDrivers() ) {
            ui->cbDrivers->addItem( driver->name(), *driver );
        }
        
        connect( ui->cbDrivers, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cbDrivers_currentIndexChanged( int ) ) );
        connect( ui->cbDrivers, SIGNAL( popupAboutToShow() ), this, SLOT( cbDrivers_popupAboutToShow() ) );
    }
    
    ~InputSearchWidgetPrivate() {
        delete ui;
    }
    
    void retranslateUi() {
        ui->retranslateUi( widget );
    }

public slots:
    void cbDrivers_currentIndexChanged( int index ) {
        if ( index != -1 ) {
            AbstractHousingDriver* driver = ui->cbDrivers->itemData( index ).value<AbstractHousingDriver*>();
            const QMap<QString, QString> rooms = driver->roomsInputs();
            const QMap<QString, QString> bedrooms = driver->bedroomsInputs();
            
            ui->cswCities->setCityQuery( driver->cityQuery() );
            
            // TODO: replace with a Fresh pCheckComboBox when possible
            ui->cbRooms->clear();
            
            foreach ( const QString& label, rooms.keys() ) {
                ui->cbRooms->addItem( label, rooms[ label ] );
            }
            
            // TODO: replace with a Fresh pCheckComboBox when possible
            ui->cbBedrooms->clear();
            
            foreach ( const QString& label, bedrooms.keys() ) {
                ui->cbBedrooms->addItem( label, bedrooms[ label ] );
            }
        }
        
        widget->loadRequestProperties();
    }
    
    void cbDrivers_popupAboutToShow() {
        widget->saveRequestProperties();
    }
};

InputSearchWidget::InputSearchWidget( QWidget* parent )
    : QScrollArea( parent ),
        d( new InputSearchWidgetPrivate( this ) )
{
}

InputSearchWidget::~InputSearchWidget()
{
}

void InputSearchWidget::setCurrentDriver( AbstractHousingDriver* driver )
{
    QComboBox* cb = d->ui->cbDrivers;
    const int currentIndex = cb->currentIndex();
    const int index = cb->findData( *driver );
    
    if ( index != -1 ) {
        if ( currentIndex != -1 && currentIndex != index ) {
            saveRequestProperties();
        }
        
        if ( cb->currentIndex() != index ) {
            cb->setCurrentIndex( index );
        }
        else {
            d->cbDrivers_currentIndexChanged( index );
        }
    }
}

AbstractHousingDriver* InputSearchWidget::currentDriver() const
{
    QComboBox* cb = d->ui->cbDrivers;
    const int index = cb->currentIndex();
    return cb->itemData( index ).value<AbstractHousingDriver*>();
}

void InputSearchWidget::setCurrentDriverName( const QString& name )
{
    foreach ( AbstractHousingDriver* driver, AbstractHousingDriver::registeredDrivers() ) {
        if ( driver->name() == name ) {
            setCurrentDriver( driver );
            return;
        }
    }
}

QString InputSearchWidget::currentDriverName() const
{
    const AbstractHousingDriver* driver = currentDriver();
    return driver ? driver->name() : QString::null;
}

void InputSearchWidget::setIgnoredId( int id, bool ignored )
{
    if ( ignored ) {
        d->ignoredIdSet << id;
    }
    else {
        d->ignoredIdSet.remove( id );
    }
}

bool InputSearchWidget::isIgnoredId( int id ) const
{
    return d->ignoredIdSet.contains( id );
}

QSet<int> InputSearchWidget::ignoredIdSet() const
{
    return d->ignoredIdSet;
}

void InputSearchWidget::setBookmarkedId( int id, bool ignored )
{
    if ( ignored ) {
        d->bookmarkedIdSet << id;
    }
    else {
        d->bookmarkedIdSet.remove( id );
    }
}

bool InputSearchWidget::isBookmarkedId( int id ) const
{
    return d->bookmarkedIdSet.contains( id );
}

QSet<int> InputSearchWidget::bookmarkedIdSet() const
{
    return d->bookmarkedIdSet;
}

void InputSearchWidget::setRequestProperties( const AbstractHousingDriver::RequestProperties& properties )
{
    QComboBox* cb = 0;
    
    if ( properties.type == AbstractHousingDriver::SearchTypeRent ) {
        d->ui->rbRent->setChecked( true );
    }
    else {
        d->ui->rbPurchase->setChecked( true );
    }
    
    cb = d->ui->cbSorting;
    cb->setCurrentIndex( cb->findData( properties.sorting ) );
    
    cb = d->ui->cbProperties;
    cb->setCurrentIndex( cb->findData( int( properties.properties ) ) );
    
    cb = d->ui->cbFeatures;
    cb->setCurrentIndex( cb->findData( int( properties.features ) ) );
    
    d->ui->cswCities->setCities( properties.cities );
    
    cb = d->ui->cbRooms;
    cb->setCurrentIndex( cb->findData( properties.numberOfRooms().value( 0 ).toString() ) );
    
    cb = d->ui->cbBedrooms;
    cb->setCurrentIndex( cb->findData( properties.numberOfBedrooms().value( 0 ).toString() ) );
    
    d->ui->sbMinBudget->setValue( properties.minimumBudget() );
    d->ui->sbMaxBudget->setValue( properties.maximumBudget() );
    d->ui->sbMinSurface->setValue( properties.minimumSurface() );
    d->ui->sbMaxSurface->setValue( properties.maximumSurface() );
    d->ui->sbMinGround->setValue( properties.minimumGround() );
    d->ui->sbMaxGround->setValue( properties.maximumGround() );
    
    d->ignoredIdSet = properties.ignoredIdSet;
    d->bookmarkedIdSet = properties.bookmarkedIdSet;
}

AbstractHousingDriver::RequestProperties InputSearchWidget::requestProperties() const
{
    AbstractHousingDriver::RequestProperties properties;
    QComboBox* cb = 0;
    
    properties.type = d->ui->rbRent->isChecked()
        ? AbstractHousingDriver::SearchTypeRent
        : AbstractHousingDriver::SearchTypePurchase
    ;
    
    cb = d->ui->cbSorting;
    properties.setSorting( cb->itemData( cb->currentIndex() ).toInt() );
    
    cb = d->ui->cbProperties;
    properties.setProperties( cb->itemData( cb->currentIndex() ).toInt() );
    
    cb = d->ui->cbFeatures;
    properties.setFeatures( cb->itemData( cb->currentIndex() ).toInt() );
    
    properties.cities = d->ui->cswCities->cities();
    
    cb = d->ui->cbRooms;
    properties.setNumberOfRooms( QVariantList() << cb->itemData( cb->currentIndex() ).toString() );
    
    cb = d->ui->cbBedrooms;
    properties.setNumberOfBedrooms( QVariantList() << cb->itemData( cb->currentIndex() ).toString() );
    
    properties.setMinimumBudget( d->ui->sbMinBudget->value() );
    properties.setMaximumBudget( d->ui->sbMaxBudget->value() );
    properties.setMinimumSurface( d->ui->sbMinSurface->value() );
    properties.setMaximumSurface( d->ui->sbMaxSurface->value() );
    properties.setMinimumGround( d->ui->sbMinGround->value() );
    properties.setMaximumGround( d->ui->sbMaxGround->value() );
    
    properties.ignoredIdSet = d->ignoredIdSet;
    properties.bookmarkedIdSet = d->bookmarkedIdSet;
    
    return properties;
}

bool InputSearchWidget::loadRequestProperties()
{
    AbstractHousingDriver* driver = currentDriver();
    
    if ( driver ) {
        const QString name = QString( "%1.properties" ).arg( driver->name() );
        QVariant variant;
        
        if ( Housing::readJsonFile( variant, name ) ) {
            setRequestProperties( AbstractHousingDriver::RequestProperties( variant ) );
            return true;
        }
    }
    
    return false;
}

bool InputSearchWidget::saveRequestProperties() const
{
    AbstractHousingDriver* driver = currentDriver();
    
    if ( driver ) {
        const QVariant variant = requestProperties().toVariant();
        const QString name = QString( "%1.properties" ).arg( driver->name() );
        return Housing::writeJsonFile( variant, name );
    }
    
    return false;
}

void InputSearchWidget::changeEvent( QEvent* event )
{
    QWidget::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        d->retranslateUi();
    }
}

#include "InputSearchWidget.moc"
