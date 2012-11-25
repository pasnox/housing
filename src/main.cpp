#include <QApplication>
#include <QLibraryInfo>
#include <QFileInfo>
#include <QDebug>

#include <FreshCore/pTranslationManager>
#include <FreshGui/pTranslationDialog>

#include "seloger/SeLogerHousingDriver.h"

#include "UIMain.h"

int main( int argc, char** argv )
{
    // init application
    QApplication app( argc, argv );
    app.setApplicationName( "Housing" );
    app.setApplicationVersion( "1.0.0" );
    app.setOrganizationDomain( "sodream.org" );
    app.setOrganizationName( "SoDream" );
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
    UIMain w;
    w.setWindowTitle( app.applicationName() );
    w.showMaximized();

    // run application
    QObject::connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
