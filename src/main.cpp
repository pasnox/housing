/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : main.cpp
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
#include <QApplication>
#include <QLibraryInfo>
#include <QFileInfo>
#include <QIcon>
#include <QDebug>

#include <FreshCore/pTranslationManager>
#include <FreshGui/pTranslationDialog>

#include "seloger/SeLogerHousingDriver.h"

#if defined( DESKTOP_UI )
    #include "mainwindow/UIDesktopMain.h"
#elif defined( MOBILE_UI )
    #include "mainwindow/UIMobileMain.h"
#else
#error Unknown interface.
#endif

int main( int argc, char** argv )
{
    // init application
    QApplication app( argc, argv );
    app.setApplicationName( "Housing" );
    app.setApplicationVersion( "1.0.0" );
    app.setOrganizationDomain( "sodream.org" );
    app.setOrganizationName( "SoDream" );
	
#if !( defined( Q_OS_UNIX ) && !defined( Q_OS_MAC ) ) || defined( Q_OS_BLACKBERRY )
	const QStringList themesPaths = QIcon::themeSearchPaths()
#if defined( Q_OS_MACX )
        << QString( "%1/../../../Resources" ).arg( QApplication::applicationDirPath() )
#elif defined( Q_OS_BLACKBERRY )
        << "app/native"
#else
        << QApplication::applicationDirPath()
#endif
	;
	
	QIcon::setThemeSearchPaths( themesPaths );
	QIcon::setThemeName( "Oxygen" );
#endif
	
    app.setWindowIcon( QIcon::fromTheme( "go-home" ) );
    
    const QStringList paths = QStringList()
        << QLibraryInfo::location( QLibraryInfo::TranslationsPath )
        << QFileInfo( __FILE__ ).absolutePath().append( "/../translations" )
#if defined( Q_OS_MACX )
        << QString( "%1/../../../translations" ).arg( QApplication::applicationDirPath() )
#else
        << QString( "%1/translations" ).arg( QApplication::applicationDirPath() )
#endif
    ;
    
    pTranslationManager* translationManager = pTranslationManager::instance();
    translationManager->setFakeCLocaleEnabled( true );
	translationManager->addTranslationsMask( "qt*.qm" );
	translationManager->addTranslationsMask( "fresh*.qm" );
	translationManager->addTranslationsMask( "housing*.qm" );
	translationManager->addForbiddenTranslationsMask( "qt_help*.qm" );
	translationManager->setCurrentLocale( QLocale::system().name() );
    translationManager->setTranslationsPaths( paths );
    translationManager->reloadTranslations();
    
    // register drivers
    AbstractHousingDriver::registerDriver( new SeLogerHousingDriver );

    // init main window
#if defined( DESKTOP_UI )
    UIDesktopMain w;
#elif defined( MOBILE_UI )
    UIMobileMain w;
#endif
    w.setWindowTitle( app.applicationName() );
    w.showMaximized();

    // run application
    QObject::connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
