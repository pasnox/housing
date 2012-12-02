/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : NetworkManager.h
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
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QVariant>

/*
    A special QNAM with native json handler
*/

class NetworkManagerPrivate;

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
    
public:
    NetworkManager( QObject* parent = 0 );
    virtual ~NetworkManager();
    
    QNetworkReply* getJson( const QNetworkRequest& request );
    QNetworkReply* postJson( const QNetworkRequest& request, QIODevice* data );
    QNetworkReply* postJson( const QNetworkRequest& request, const QByteArray& data );
    QNetworkReply* postJson( const QNetworkRequest& request, QHttpMultiPart* multiPart );
    
    QNetworkReply* getImage( const QNetworkRequest& request );
    QNetworkReply* postImage( const QNetworkRequest& request, QIODevice* data );
    QNetworkReply* postImage( const QNetworkRequest& request, const QByteArray& data );
    QNetworkReply* postImage( const QNetworkRequest& request, QHttpMultiPart* multiPart );
    
    static NetworkManager* instance();

private:
    NetworkManagerPrivate* d;

signals:
    void jsonFinished( QNetworkReply* reply, const QByteArray& data, const QVariantMap& json );
    void imageFinished( QNetworkReply* reply, const QByteArray& data, const QPixmap& pixmap );
};

#endif // NETWORKMANAGER_H
