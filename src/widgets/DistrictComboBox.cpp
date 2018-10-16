/****************************************************************************
**
** 
** Authors   : don-vip
** Project   : Housing
** FileName  : DistrictComboBox.cpp
** Date      : 2015-09-06T00:17:14
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
#include "DistrictComboBox.h"
#include "interface/DistrictModel.h"
#include "interface/AbstractDistrictQuery.h"

#include <QCompleter>
#include <QToolTip>
#include <QAbstractItemView>
#include <QTimer>
#include <QLineEdit>
#include <QDebug>

class DistrictComboBoxPrivate : public QObject {
    Q_OBJECT

public:
    DistrictComboBox* comboBox;
    DistrictModel* model;
    QTimer* timer;
    AbstractDistrictQuery* query;

public:
    DistrictComboBoxPrivate( DistrictComboBox* _cb )
        : QObject( _cb ),
        comboBox( _cb ),
        model( new DistrictModel( this ) ),
        timer( new QTimer( this ) ),
        query( 0 )
    {
        comboBox->setEditable( true );
        comboBox->setModel( model );
        comboBox->setModelColumn( 0 );
        comboBox->lineEdit()->setPlaceholderText( DistrictComboBox::tr( "Type a district name / zip code..." ) );
        timer->setInterval( 500 );
        timer->setSingleShot( true );
        
        connect( comboBox->lineEdit(), SIGNAL( textEdited( const QString& ) ), timer, SLOT( start() ) );
        connect( timer, SIGNAL( timeout() ), this, SLOT( updateQuery() ) );
    }

private slots:
    void updateQuery() {
        if ( !query ) {
            comboBox->setToolTip( DistrictComboBox::tr( "No AbstractDistrictQuery set." ) );
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
    
    void districtsReceived( const District::List& districts ) {
        model->setDistricts( districts );
        
        if ( !districts.isEmpty() ) {
            comboBox->showPopup();
        }
    }
};

DistrictComboBox::DistrictComboBox( QWidget* parent )
    : pComboBox( parent ),
        d( new DistrictComboBoxPrivate( this ) )
{
}

DistrictComboBox::~DistrictComboBox()
{
}

void DistrictComboBox::setDistrictQuery( AbstractDistrictQuery* query )
{
   if ( d->query == query ) {
        return;
    }
    
    if ( d->query ) {
        disconnect( d->query, SIGNAL( error( const QString& ) ), d, SLOT( setToolTip( const QString& ) ) );
        disconnect( d->query, SIGNAL( districtsReceived( const District::List& ) ), d, SLOT( districtsReceived( const District::List& ) ) );
        d->query->deleteLater();
    }
    
    d->query = query;
    
    if ( d->query ) {
        d->query->setParent( this );
        connect( d->query, SIGNAL( error( const QString& ) ), d, SLOT( setToolTip( const QString& ) ) );
        connect( d->query, SIGNAL( districtsReceived( const District::List& ) ), d, SLOT( districtsReceived( const District::List& ) ) );
    }
}

AbstractDistrictQuery* DistrictComboBox::districtQuery() const
{
    return d->query;
}

District DistrictComboBox::district() const
{
    return d->model->district( d->model->index( currentIndex(), modelColumn() ) );
}

#include "DistrictComboBox.moc"
