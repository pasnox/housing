#include "CityComboBox.h"
#include "interface/CityModel.h"
#include "interface/AbstractCityQuery.h"

#include <QCompleter>
#include <QToolTip>
#include <QAbstractItemView>
#include <QTimer>
#include <QLineEdit>
#include <QDebug>

class CityComboBoxPrivate : public QObject {
    Q_OBJECT

public:
    CityComboBox* comboBox;
    CityModel* model;
    QTimer* timer;
    AbstractCityQuery* query;

public:
    CityComboBoxPrivate( CityComboBox* _cb )
        : QObject( _cb ),
        comboBox( _cb ),
        model( new CityModel( this ) ),
        timer( new QTimer( this ) ),
        query( 0 )
    {
        comboBox->setEditable( true );
        comboBox->setModel( model );
        comboBox->setModelColumn( 0 );
        comboBox->lineEdit()->setPlaceholderText( tr( "Type a city name / zip code..." ) );
        timer->setInterval( 500 );
        timer->setSingleShot( true );
        
        connect( comboBox->lineEdit(), SIGNAL( textEdited( const QString& ) ), timer, SLOT( start() ) );
        connect( timer, SIGNAL( timeout() ), this, SLOT( updateQuery() ) );
    }

private slots:
    void updateQuery() {
        if ( !query ) {
            comboBox->setToolTip( CityComboBox::tr( "No AbstractCityQuery setted." ) );
            return;
        }
        
        const QString text = comboBox->lineEdit()->text();
        
        if ( text.length() < query->minimumSearchLength() ) {
            return;
        }
        
        query->search( text );
    }
    
    void setToolTip( const QString& text ) {
        comboBox->setToolTip( text );
        QToolTip::showText( comboBox->mapToGlobal( QPoint( 1, 1 ) ), text, comboBox );
    }
    
    void citiesReceived( const City::List& cities ) {
        model->setCities( cities );
        
        if ( !cities.isEmpty() ) {
            comboBox->showPopup();
        }
    }
};

CityComboBox::CityComboBox( QWidget* parent )
    : pComboBox( parent ),
        d( new CityComboBoxPrivate( this ) )
{
}

CityComboBox::~CityComboBox()
{
}

void CityComboBox::setCityQuery( AbstractCityQuery* query )
{
    if ( d->query == query ) {
        return;
    }
    
    if ( d->query ) {
        disconnect( d->query, SIGNAL( error( const QString& ) ), d, SLOT( setToolTip( const QString& ) ) );
        disconnect( d->query, SIGNAL( citiesReceived( const City::List& ) ), d, SLOT( citiesReceived( const City::List& ) ) );
        d->query->deleteLater();
    }
    
    d->query = query;
    
    if ( d->query ) {
        d->query->setParent( this );
        connect( d->query, SIGNAL( error( const QString& ) ), d, SLOT( setToolTip( const QString& ) ) );
        connect( d->query, SIGNAL( citiesReceived( const City::List& ) ), d, SLOT( citiesReceived( const City::List& ) ) );
    }
}

AbstractCityQuery* CityComboBox::cityQuery() const
{
    return d->query;
}

City CityComboBox::city() const
{
    return d->model->city( d->model->index( currentIndex(), modelColumn() ) );
}

#include "CityComboBox.moc"
