#include <QApplication>

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
