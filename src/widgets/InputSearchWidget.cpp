/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : InputSearchWidget.cpp
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
#include "InputSearchWidget.h"
#include "ui_InputSearchWidget.h"
#include "objects/Housing.h"

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
        
        ui->bgType->setId( ui->rbPurchase, AbstractHousingDriver::SearchTypePurchase );
        ui->bgType->setId( ui->rbRent, AbstractHousingDriver::SearchTypeRent );
        
        ui->cbProperties->addItem( InputSearchWidget::tr( "All" ), AbstractHousingDriver::SearchPropertyAll );
        ui->cbProperties->addSeparator();
        ui->cbProperties->addItem( InputSearchWidget::tr( "Apartment" ), AbstractHousingDriver::SearchPropertyApartment );
        ui->cbProperties->addItem( InputSearchWidget::tr( "House / Villa" ), AbstractHousingDriver::SearchPropertyHouseOrVilla );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Parking / Box" ), AbstractHousingDriver::SearchPropertyParkingOrBox );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Ground" ), AbstractHousingDriver::SearchPropertyGround );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Shop" ), AbstractHousingDriver::SearchPropertyShop );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Commercial Local" ), AbstractHousingDriver::SearchPropertyCommercialLocal );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Offices" ), AbstractHousingDriver::SearchPropertyOffices );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Loft / Workshop / Surface" ), AbstractHousingDriver::SearchPropertyLoftOrWorkshopOrSurface );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Tenement" ), AbstractHousingDriver::SearchPropertyTenement );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Building" ), AbstractHousingDriver::SearchPropertyBuilding );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Castle" ), AbstractHousingDriver::SearchPropertyCastle );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Mansion" ), AbstractHousingDriver::SearchPropertyMansion );
        ui->cbProperties->addItem( InputSearchWidget::tr( "Others" ), AbstractHousingDriver::SearchPropertyOthers );
        
        ui->cbSorting->addItem( InputSearchWidget::tr( "None" ), AbstractHousingDriver::SearchSortingNone );
        ui->cbSorting->addItem( InputSearchWidget::tr( "Ascending date" ), AbstractHousingDriver::SearchSortingAscendingDate );
        ui->cbSorting->addItem( InputSearchWidget::tr( "Descending date" ), AbstractHousingDriver::SearchSortingDescendingDate );
        ui->cbSorting->addItem( InputSearchWidget::tr( "Ascending price" ), AbstractHousingDriver::SearchSortingAscendingPrice );
        ui->cbSorting->addItem( InputSearchWidget::tr( "Descending price" ), AbstractHousingDriver::SearchSortingDescendingPrice );
        ui->cbSorting->addItem( InputSearchWidget::tr( "Ascending surface" ), AbstractHousingDriver::SearchSortingAscendingSurface );
        ui->cbSorting->addItem( InputSearchWidget::tr( "Descending surface" ), AbstractHousingDriver::SearchSortingDescendingSurface );
        
        ui->cbFeatures->addItem( InputSearchWidget::tr( "All" ), AbstractHousingDriver::SearchFeatureAll );
        ui->cbFeatures->addSeparator();
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Elevator" ), AbstractHousingDriver::SearchFeatureElevator );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Digicode" ), AbstractHousingDriver::SearchFeatureDigicode );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Intercom" ), AbstractHousingDriver::SearchFeatureIntercom );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Caretaker" ), AbstractHousingDriver::SearchFeatureCaretaker );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Pool" ), AbstractHousingDriver::SearchFeaturePool );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Terrace" ), AbstractHousingDriver::SearchFeatureTerrace );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Balcony" ), AbstractHousingDriver::SearchFeatureBalcony );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Parking" ), AbstractHousingDriver::SearchFeatureParking );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Box" ), AbstractHousingDriver::SearchFeatureBox );
        ui->cbFeatures->addItem( InputSearchWidget::tr( "Cellar" ), AbstractHousingDriver::SearchFeatureCellar );
        
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
            ui->cswDistricts->setDistrictQuery( driver->districtQuery() );
            ui->cbRooms->clear();
            ui->cbBedrooms->clear();
            
            foreach ( const QString& label, rooms.keys() ) {
                if ( rooms[ label ] == "all" ) {
                    ui->cbRooms->insertItem( 0, label, rooms[ label ] );
                    ui->cbRooms->insertSeparator( 1 );
                }
                else {
                    ui->cbRooms->addItem( label, rooms[ label ] );
                }
            }
            
            foreach ( const QString& label, bedrooms.keys() ) {
                if ( bedrooms[ label ] == "all" ) {
                    ui->cbBedrooms->insertItem( 0, label, bedrooms[ label ] );
                    ui->cbBedrooms->insertSeparator( 1 );
                }
                else {
                    ui->cbBedrooms->addItem( label, bedrooms[ label ] );
                }
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
    QAbstractButton* button = d->ui->bgType->button( properties.type );
    QComboBox* cb = 0;
    
    if ( !button ) {
        button = d->ui->rbPurchase;
    }
    
    button->setChecked( true );
    
    cb = d->ui->cbSorting;
    cb->setCurrentIndex( cb->findData( int( properties.sorting ) ) );
    
    cb = d->ui->cbProperties;
    for ( int i = 0; i < cb->count(); i++ ) {
        const int flag = cb->itemData( i, Qt::UserRole ).toInt();
        bool check = properties.properties & flag;
        
        if ( check && flag == AbstractHousingDriver::SearchPropertyAll ) {
            check = flag == properties.properties;
        }
        
        cb->setItemData( i, check ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole );
    }
    
    cb = d->ui->cbFeatures;
    for ( int i = 0; i < cb->count(); i++ ) {
        const int flag = cb->itemData( i, Qt::UserRole ).toInt();
        bool check = properties.features & flag;
        
        if ( check && flag == AbstractHousingDriver::SearchFeatureAll ) {
            check = flag == properties.features;
        }
        
        cb->setItemData( i, check ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole );
    }
    
    d->ui->cswCities->setCities( properties.cities );
    d->ui->cswDistricts->setDistricts( properties.districts );
    
    cb = d->ui->cbRooms;
    const QSet<QVariant> roomsSet = properties.numberOfRooms().toSet();
    for ( int i = 0; i < cb->count(); i++ ) {
        const QVariant flag = cb->itemData( i, Qt::UserRole );
        bool check = roomsSet.contains( flag );
        cb->setItemData( i, check ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole );
    }
    
    cb = d->ui->cbBedrooms;
    const QSet<QVariant> bedroomsSet = properties.numberOfBedrooms().toSet();
    for ( int i = 0; i < cb->count(); i++ ) {
        const QVariant flag = cb->itemData( i, Qt::UserRole );
        bool check = bedroomsSet.contains( flag );
        cb->setItemData( i, check ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole );
    }
    
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
    
    properties.type = AbstractHousingDriver::SearchType( d->ui->bgType->checkedId() );
    
    cb = d->ui->cbSorting;
    properties.sorting = AbstractHousingDriver::SearchSortingFlag( cb->itemData( cb->currentIndex() ).toInt() );
    
    cb = d->ui->cbProperties;
    for ( int i = 0; i < cb->count(); i++ ) {
        const bool isChecked = cb->itemData( i, Qt::CheckStateRole ).toInt() == Qt::Checked;
        
        if ( isChecked ) {
            const int flag = cb->itemData( i, Qt::UserRole ).toInt();
            properties.properties |= AbstractHousingDriver::SearchProperty( flag );
        }
    }
    
    cb = d->ui->cbFeatures;
    for ( int i = 0; i < cb->count(); i++ ) {
        const bool isChecked = cb->itemData( i, Qt::CheckStateRole ).toInt() == Qt::Checked;
        
        if ( isChecked ) {
            const int flag = cb->itemData( i, Qt::UserRole ).toInt();
            properties.features |= AbstractHousingDriver::SearchFeature( flag );
        }
    }
    
    properties.cities = d->ui->cswCities->cities();
    properties.districts = d->ui->cswDistricts->districts();
    
    cb = d->ui->cbRooms;
    QVariantList rooms;
    for ( int i = 0; i < cb->count(); i++ ) {
        const bool isChecked = cb->itemData( i, Qt::CheckStateRole ).toInt() == Qt::Checked;
        
        if ( isChecked ) {
            const QVariant flag = cb->itemData( i, Qt::UserRole );
            rooms << flag;
        }
    }
    properties.setNumberOfRooms( rooms );
    
    cb = d->ui->cbBedrooms;
    QVariantList bedrooms;
    for ( int i = 0; i < cb->count(); i++ ) {
        const bool isChecked = cb->itemData( i, Qt::CheckStateRole ).toInt() == Qt::Checked;
        
        if ( isChecked ) {
            const QVariant flag = cb->itemData( i, Qt::UserRole );
            bedrooms << flag;
        }
    }
    properties.setNumberOfBedrooms( bedrooms );
    
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
