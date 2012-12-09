/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : Housing.h
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
    bool removeJsonFile( const QString& name );
    
    QString googleMapGPSUrl( const double& latitude, const double& longitude, char viewType = 'h', int zoom = 15 );
};

#endif // HOUSING_H
