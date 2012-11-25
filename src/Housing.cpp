#include "Housing.h"

#include "parser.h"
#include "serializer.h"

#include <QTextDocument>
#include <QDesktopServices>
#include <QFile>
#include <QDir>
#include <QDebug>

QString Housing::toPlainText( const QString& html )
{
    static QTextDocument document;
    document.setHtml( html );
    return document.toPlainText();
}

QVariant Housing::fromJson( const QByteArray& json, bool* ok )
{
    QJson::Parser parser;
    bool result = false;
    const QVariant variant = parser.parse( json, &result );
    
    if ( ok ) {
        *ok = result;
    }
    
    return variant;
}

QByteArray Housing::toJson( const QVariant& variant, bool* ok )
{
    QJson::Serializer serializer;
    const QByteArray json = serializer.serialize( variant );
    
    if ( ok ) {
        *ok = !json.isNull();
    }
    
    return json;
}

QString Housing::settingsFilePath( const QString& extended )
{
    return QDir::toNativeSeparators( QDir::cleanPath(
        QDesktopServices::storageLocation( QDesktopServices::DataLocation )
            .append( "/" )
            .append( extended )
    ) );
}

bool Housing::readJsonFile( QVariant& variant, const QString& name )
{
    const QFileInfo fi( Housing::settingsFilePath( name ) );
    
    if ( fi.exists() ) {
        QFile file( fi.absoluteFilePath() );
        
        if ( !file.open( QIODevice::ReadOnly ) ) {
            qWarning( "%s: Can not open for reading %s", Q_FUNC_INFO, qPrintable( file.fileName() ) );
            return false;
        }
        
        bool ok;
        
        variant = Housing::fromJson( file.readAll(), &ok );
        
        return ok;
    }
    
    return false;
}

bool Housing::writeJsonFile( const QVariant& variant, const QString& name )
{
    const QFileInfo fi( Housing::settingsFilePath( name ) );
    const QString path = fi.absolutePath();
    
    if ( !QFile::exists( path ) ) {
        if ( !QDir().mkpath( path ) ) {
            qWarning( "%s: Can not create path %s", Q_FUNC_INFO, qPrintable( path ) );
            return false;
        }
    }
    
    QFile file( fi.absoluteFilePath() );
    
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) ) {
        qWarning( "%s: Can not open for writing %s", Q_FUNC_INFO, qPrintable( file.fileName() ) );
        return false;
    }
    
    bool ok;
    
    if ( file.write( Housing::toJson( variant, &ok ) ) == -1 ) {
        qWarning( "%s: Can not write in %s", Q_FUNC_INFO, qPrintable( file.fileName() ) );
        return false;
    }
    
    return ok;
}
