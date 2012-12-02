/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : NetworkManager.cpp
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
#include "NetworkManager.h"
#include "Housing.h"

#include <QPointer>
#include <QApplication>
#include <QSet>
#include <QUrl>
#include <QNetworkReply>
#include <QPixmap>
#include <QDebug>

static QPointer<NetworkManager> NetworkManagerInstance;

class NetworkManagerPrivate : public QObject {
    Q_OBJECT
    
public:
    NetworkManager* nm;
    QSet<QUrl> jsonReplies;
    QSet<QUrl> imageReplies;

public:
    NetworkManagerPrivate( NetworkManager* _nm )
        : QObject( _nm ),
            nm( _nm )
    {
        connect( nm, SIGNAL( authenticationRequired( QNetworkReply*, QAuthenticator* ) ), this, SLOT( authenticationRequired( QNetworkReply*, QAuthenticator* ) ) );
        connect( nm, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( finished( QNetworkReply* ) ) );
        connect( nm, SIGNAL( networkAccessibleChanged( QNetworkAccessManager::NetworkAccessibility ) ), this, SLOT( networkAccessibleChanged( QNetworkAccessManager::NetworkAccessibility ) ) );
        connect( nm, SIGNAL( proxyAuthenticationRequired( const QNetworkProxy&, QAuthenticator* ) ), this, SLOT( proxyAuthenticationRequired( const QNetworkProxy&, QAuthenticator* ) ) );
        connect( nm, SIGNAL( sslErrors( QNetworkReply*, const QList<QSslError>& ) ), this, SLOT( sslErrors( QNetworkReply*, const QList<QSslError>& ) ) );
        connect( this, SIGNAL( jsonFinished( QNetworkReply*, const QByteArray&, const QVariantMap& ) ), nm, SIGNAL( jsonFinished( QNetworkReply*, const QByteArray&, const QVariantMap& ) ) );
        connect( this, SIGNAL( imageFinished( QNetworkReply*, const QByteArray&, const QPixmap& ) ), nm, SIGNAL( imageFinished( QNetworkReply*, const QByteArray&, const QPixmap& ) ) );
    }

private slots:
    void authenticationRequired( QNetworkReply* reply, QAuthenticator* authenticator ) {
        qWarning( "%s:", Q_FUNC_INFO );
        Q_UNUSED( reply );
        Q_UNUSED( authenticator );
    }
    
    void finished( QNetworkReply* reply ) {
        //qWarning( "%s:", Q_FUNC_INFO );
        
        if ( jsonReplies.contains( reply->request().url() ) ) {
            const QByteArray json = reply->readAll();
            QVariantMap data;
            
            if ( reply->error() == QNetworkReply::NoError ) {
                bool ok;
                
                data[ "json" ] = Housing::fromJson( json, &ok );
                data[ "success" ] = ok;
                data[ "message" ] = QString();
            }
            else {
                data[ "json" ] = QVariant();
                data[ "success" ] = false;
                data[ "message" ] = NetworkManager::tr( "Invalid content received." );
            }
            
            jsonReplies.remove( reply->request().url() );
            
            emit jsonFinished( reply, json, data );
        }
        else if ( imageReplies.contains( reply->request().url() ) ) {
            const QByteArray data = reply->readAll();
            QPixmap pixmap;
            
            pixmap.loadFromData( data );
            
            imageReplies.remove( reply->request().url() );
            
            emit imageFinished( reply, data, pixmap );
        }
        
        reply->deleteLater();
    }
    
    void networkAccessibleChanged( QNetworkAccessManager::NetworkAccessibility accessible ) {
        qWarning( "%s:", Q_FUNC_INFO );
        Q_UNUSED( accessible );
    }
    
    void proxyAuthenticationRequired( const QNetworkProxy& proxy, QAuthenticator* authenticator ) {
        qWarning( "%s:", Q_FUNC_INFO );
        Q_UNUSED( proxy );
        Q_UNUSED( authenticator );
    }
    
    void sslErrors( QNetworkReply* reply, const QList<QSslError>& errors ) {
        qWarning( "%s:", Q_FUNC_INFO );
        Q_UNUSED( errors );
        reply->ignoreSslErrors();
    }

signals:
    void jsonFinished( QNetworkReply* reply, const QByteArray& data, const QVariantMap& json );
    void imageFinished( QNetworkReply* reply, const QByteArray& data, const QPixmap& pixmap );
};

NetworkManager::NetworkManager( QObject* parent )
    : QNetworkAccessManager( parent ),
        d( new NetworkManagerPrivate( this ) )
{
}

NetworkManager::~NetworkManager()
{
}

QNetworkReply* NetworkManager::getJson( const QNetworkRequest& request )
{
    if ( !d->jsonReplies.contains( request.url() ) ) {
        d->jsonReplies << request.url();
        return QNetworkAccessManager::get( request );
    }
    
    return 0;
}

QNetworkReply* NetworkManager::postJson( const QNetworkRequest& request, QIODevice* data )
{
    if ( !d->jsonReplies.contains( request.url() ) ) {
        d->jsonReplies << request.url();
        return QNetworkAccessManager::post( request, data );
    }
    
    return 0;
}

QNetworkReply* NetworkManager::postJson( const QNetworkRequest& request, const QByteArray& data )
{
    if ( !d->jsonReplies.contains( request.url() ) ) {
        d->jsonReplies << request.url();
        return QNetworkAccessManager::post( request, data );
    }
    
    return 0;
}

QNetworkReply* NetworkManager::postJson( const QNetworkRequest& request, QHttpMultiPart* multiPart )
{
    if ( !d->jsonReplies.contains( request.url() ) ) {
        d->jsonReplies << request.url();
        return QNetworkAccessManager::post( request, multiPart );
    }
    
    return 0;
}

QNetworkReply* NetworkManager::getImage( const QNetworkRequest& request )
{
    if ( !d->imageReplies.contains( request.url() ) ) {
        d->imageReplies << request.url();
        return QNetworkAccessManager::get( request );
    }
    
    return 0;
}

QNetworkReply* NetworkManager::postImage( const QNetworkRequest& request, QIODevice* data )
{
    if ( !d->imageReplies.contains( request.url() ) ) {
        d->imageReplies << request.url();
        return QNetworkAccessManager::post( request, data );
    }
    
    return 0;
}

QNetworkReply* NetworkManager::postImage( const QNetworkRequest& request, const QByteArray& data )
{
    if ( !d->imageReplies.contains( request.url() ) ) {
        d->imageReplies << request.url();
        return QNetworkAccessManager::post( request, data );
    }
    
    return 0;
}

QNetworkReply* NetworkManager::postImage( const QNetworkRequest& request, QHttpMultiPart* multiPart )
{
    if ( !d->imageReplies.contains( request.url() ) ) {
        d->imageReplies << request.url();
        return QNetworkAccessManager::post( request, multiPart );
    }
    
    return 0;
}

NetworkManager* NetworkManager::instance()
{
    if ( !NetworkManagerInstance ) {
        NetworkManagerInstance = new NetworkManager( qApp );
    }
    
    return NetworkManagerInstance;
}

#include "NetworkManager.moc"
