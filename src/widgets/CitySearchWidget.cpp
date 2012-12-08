/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : CitySearchWidget.cpp
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
#include "CitySearchWidget.h"
#include "ui_CitySearchWidget.h"
#include "interface/AbstractCityQuery.h"
#include "interface/CityModel.h"

#include <QEvent>
#include <QMessageBox>
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
        const QString title = QString::null;
        const QString message = CitySearchWidget::tr( "Are you sure you want to clear the list ?" );
        const QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No;
        const QMessageBox::StandardButton defaultButton = QMessageBox::No;
        
        if ( QMessageBox::question( widget->window(), title, message, buttons, defaultButton ) == defaultButton ) {
            return;
        }
        
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
