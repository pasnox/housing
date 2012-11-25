#include "CitySearchWidget.h"
#include "ui_CitySearchWidget.h"
#include "interface/AbstractCityQuery.h"
#include "interface/CityModel.h"

#include <QEvent>
#include <QDebug>

class CitySearchWidgetPrivate : public QObject {
    Q_OBJECT

public:
    CitySearchWidget* widget;
    Ui_CitySearchWidget* ui;
    CityModel* model;
    
public:
    CitySearchWidgetPrivate( CitySearchWidget* _widget )
        : QObject( _widget ),
            widget( _widget ),
            ui( new Ui_CitySearchWidget ),
            model( new CityModel( this ) )
    {
        ui->setupUi( widget );
        ui->lvCities->setModel( model );
        
        model->setCodeVisible( true );
        
        updateButtons();
        
        connect( ui->tbCityAdd, SIGNAL( clicked() ), this, SLOT( addCity() ) );
        connect( ui->tbCityRemove, SIGNAL( clicked() ), this, SLOT( removeCities() ) );
        connect( ui->tbCityClear, SIGNAL( clicked() ), this, SLOT( clearCities() ) );
        connect( ui->lvCities->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( rowsInserted( const QModelIndex&, int, int ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( rowsRemoved( const QModelIndex&, int, int ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( layoutChanged() ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( modelReset() ), this, SLOT( updateButtons() ) );
    }
    
    ~CitySearchWidgetPrivate() {
        delete ui;
    }
    
    void retranslateUi() {
        ui->retranslateUi( widget );
    }

private slots:
    void addCity() {
        model->addCity( ui->cbCity->city() );
    }
    
    void removeCities() {
        model->removeCities( ui->lvCities->selectionModel()->selectedIndexes() );
    }
    
    void clearCities() {
        model->clear();
    }
    
    void updateButtons() {
        const bool hasCities = model->rowCount() > 0;
        const bool hasSelection = !ui->lvCities->selectionModel()->selectedIndexes().isEmpty();
        
        ui->tbCityRemove->setEnabled( hasSelection );
        ui->tbCityClear->setEnabled( hasCities );
    }
};

CitySearchWidget::CitySearchWidget( QWidget* parent )
    : QWidget( parent ),
        d( new CitySearchWidgetPrivate( this ) )
{
}

CitySearchWidget::~CitySearchWidget()
{
}

void CitySearchWidget::setCityQuery( AbstractCityQuery* query )
{
    d->ui->cbCity->setCityQuery( query );
}

AbstractCityQuery* CitySearchWidget::cityQuery() const
{
    return d->ui->cbCity->cityQuery();
}

void CitySearchWidget::setCities( const City::List& cities )
{
    d->model->setCities( cities );
}

City::List CitySearchWidget::cities() const
{
    return d->model->cities();
}

void CitySearchWidget::setCodeVisible( bool visible )
{
    d->model->setCodeVisible( visible );
}

bool CitySearchWidget::isCodeVisible() const
{
    return d->model->isCodeVisible();
}

void CitySearchWidget::changeEvent( QEvent* event )
{
    QWidget::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        d->retranslateUi();
    }
}

#include "CitySearchWidget.moc"
