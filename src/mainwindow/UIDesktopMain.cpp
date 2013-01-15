/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : UIDesktopMain.cpp
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
#include "UIDesktopMain.h"
#include "ui_UIDesktopMain.h"
#include "UIMain_p.h"

#include <QEvent>
#include <QSettings>
#include <QDebug>

UIDesktopMain::UIDesktopMain( QWidget* parent )
    : QMainWindow( parent ),
        d( new UIMainPrivate( this ) )
{
}

UIDesktopMain::~UIDesktopMain()
{
}

void UIDesktopMain::changeEvent( QEvent* event )
{
    QMainWindow::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        d->retranslateUi();
    }
}

void UIDesktopMain::showEvent( QShowEvent* event )
{
    QMainWindow::showEvent( event );
    
    const QSettings settings;
    
    restoreGeometry( settings.value( "MainWindow/Geometry" ).toByteArray() );
    restoreState( settings.value( "MainWindow/State" ).toByteArray() );
    d->proxy->filterAction()->setChecked( settings.value( "MainWindow/FilterIgnored" ).toBool() );
    d->ui->iswSearch->setCurrentDriverName( settings.value( "MainWindow/CurrentDriverName" ).toString() );
    d->ui->iswSearch->loadRequestProperties();
}

void UIDesktopMain::closeEvent( QCloseEvent* event )
{
    const AbstractHousingDriver* driver = d->ui->iswSearch->currentDriver();
    QSettings settings;
    
    settings.setValue( "MainWindow/Geometry", saveGeometry() );
    settings.setValue( "MainWindow/State", saveState() );
    settings.setValue( "MainWindow/FilterIgnored", d->proxy->filterAction()->isChecked() );
    settings.setValue( "MainWindow/CurrentDriverName", driver ? driver->name() : QString::null );
    d->ui->iswSearch->saveRequestProperties();
    d->ui->fwFeedback->saveFileName( d->feedbackFileName( d->selectedSourceIndex() ) );
    
    QMainWindow::closeEvent( event );
}
