#ifndef HOUSING_H
#define HOUSING_H

#include <QString>
#include <QByteArray>
#include <QString>
#include <QVariant>

namespace Housing
{
    QString toPlainText( const QString& html );
    
    QVariant fromJson( const QByteArray& json, bool* ok = 0 );
    QByteArray toJson( const QVariant& variant, bool* ok = 0 );
    
    QString settingsFilePath( const QString& extended = QString::null );
    
    bool readJsonFile( QVariant& variant, const QString& name );
    bool writeJsonFile( const QVariant& variant, const QString& name );
};

#endif // HOUSING_H
