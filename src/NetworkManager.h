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
