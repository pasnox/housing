/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : DistrictSearchWidget.cpp
** Date      : 2015-09-06T00:26:14
** License   : GPL3
** Home Page : https://github.com/don-vip/housing
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
#include "DistrictSearchWidget.h"
#include "ui_DistrictSearchWidget.h"
#include "interface/AbstractDistrictQuery.h"
#include "interface/DistrictModel.h"

#include <QEvent>
#include <QMessageBox>
#include <QDebug>

class DistrictSearchWidgetPrivate : public QObject {
    Q_OBJECT

public:
    DistrictSearchWidget* widget;
    Ui_DistrictSearchWidget* ui;
    DistrictModel* model;
    
public:
    DistrictSearchWidgetPrivate( DistrictSearchWidget* _widget )
        : QObject( _widget ),
            widget( _widget ),
            ui( new Ui_DistrictSearchWidget ),
            model( new DistrictModel( this ) )
    {
        ui->setupUi( widget );
        ui->lvDistricts->setModel( model );
        
        model->setCodeVisible( true );
        
        updateButtons();
        
        connect( ui->tbDistrictAdd, SIGNAL( clicked() ), this, SLOT( addDistrict() ) );
        connect( ui->tbDistrictRemove, SIGNAL( clicked() ), this, SLOT( removeDistricts() ) );
        connect( ui->tbDistrictClear, SIGNAL( clicked() ), this, SLOT( clearDistricts() ) );
        connect( ui->lvDistricts->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( rowsInserted( const QModelIndex&, int, int ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( rowsRemoved( const QModelIndex&, int, int ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( layoutChanged() ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( modelReset() ), this, SLOT( updateButtons() ) );
    }
    
    ~DistrictSearchWidgetPrivate() {
        delete ui;
    }
    
    void retranslateUi() {
        ui->retranslateUi( widget );
    }

private slots:
    void addDistrict() {
        model->addDistrict( ui->cbDistrict->district() );
    }
    
    void removeDistricts() {
        model->removeDistricts( ui->lvDistricts->selectionModel()->selectedIndexes() );
    }
    
    void clearDistricts() {
        const QString title = QString::null;
        const QString message = DistrictSearchWidget::tr( "Are you sure you want to clear the list ?" );
        const QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No;
        const QMessageBox::StandardButton defaultButton = QMessageBox::No;
        
        if ( QMessageBox::question( widget->window(), title, message, buttons, defaultButton ) == defaultButton ) {
            return;
        }
        
        model->clear();
    }
    
    void updateButtons() {
        const bool hasDistricts = model->rowCount() > 0;
        const bool hasSelection = !ui->lvDistricts->selectionModel()->selectedIndexes().isEmpty();
        
        ui->tbDistrictRemove->setEnabled( hasSelection );
        ui->tbDistrictClear->setEnabled( hasDistricts );
    }
};

DistrictSearchWidget::DistrictSearchWidget( QWidget* parent )
    : QWidget( parent ),
        d( new DistrictSearchWidgetPrivate( this ) )
{
}

DistrictSearchWidget::~DistrictSearchWidget()
{
}

void DistrictSearchWidget::setDistrictQuery( AbstractDistrictQuery* query )
{
    d->ui->cbDistrict->setDistrictQuery( query );
}

AbstractDistrictQuery* DistrictSearchWidget::districtQuery() const
{
    return d->ui->cbDistrict->districtQuery();
}

void DistrictSearchWidget::setDistricts( const District::List& districts )
{
    d->model->setDistricts( districts );
}

District::List DistrictSearchWidget::districts() const
{
    return d->model->districts();
}

void DistrictSearchWidget::setCodeVisible( bool visible )
{
    d->model->setCodeVisible( visible );
}

bool DistrictSearchWidget::isCodeVisible() const
{
    return d->model->isCodeVisible();
}

void DistrictSearchWidget::changeEvent( QEvent* event )
{
    QWidget::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        d->retranslateUi();
    }
}

#include "DistrictSearchWidget.moc"
