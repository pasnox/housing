// Default empty project template
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>
#include "Housingbbx.hpp"

using namespace bb::cascades;
void myMessageOutput(QtMsgType type, const char* msg){
               fprintf(stdout, "%s\n", msg);
               fflush(stdout);
}

int main(int argc, char **argv)
{

	Application app(argc, argv);
	qInstallMsgHandler(myMessageOutput);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "housingbbx_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    new Housingbbx(&app);

    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
