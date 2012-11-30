#include "UIMain.h"
#include "ui_UIMain.h"
#include "interface/AnnouncementModel.h"
#include "interface/AnnouncementProxyModel.h"
#include "NetworkManager.h"

#include <QEvent>
#include <QNetworkReply>
#include <QPixmapCache>
#include <QWebView>
#include <QSettings>
#include <QMovie>
#include <QDesktopServices>
#include <QDebug>

#define TEST_CASE_DEBUG false

class UIMainPrivate : public QObject {
    Q_OBJECT

public:
    UIMain* widget;
    Ui_UIMain* ui;
    QMovie* movie;
    QLabel* movieLabel;
    AnnouncementModel* model;
    AnnouncementProxyModel* proxy;

public:
    UIMainPrivate( UIMain* _widget )
        : QObject( _widget ),
            widget( _widget ),
            ui( new Ui_UIMain ),
            movie( new QMovie( ":/animations/loading.gif" ) ),
            movieLabel( new QLabel ),
            model( new AnnouncementModel( this ) ),
            proxy( new AnnouncementProxyModel( model ) )
    {
        movie->setSpeed( 70 );
        movie->setScaledSize( QSize( 15, 15 ) );
        movie->start();
        
        movieLabel->setMovie( movie );
        
        ui->setupUi( widget );
        ui->lvAnnouncements->setModel( proxy );
        ui->lvAnnouncements->addActions( ui->tbActions->actions() );
        ui->dwInputSearch->toggleViewAction()->setIcon( ui->twPages->tabIcon( 0 ) );
        ui->tbActions->addSeparator();
        ui->tbActions->addAction( proxy->filterAction() );
        ui->tbActions->addSeparator();
        ui->tbActions->addAction( ui->dwInputSearch->toggleViewAction() );
        ui->lLegend->setText(
            QString( "<html><head/><body><p><span style=\"text-decoration: line-through; color:#a0a0a0;\">%1</span> | <span style=\"font-weight:600;\">%2</span> | <span style=\"color:#0000ff;\">%3</span></p></body></html>" )
                .arg( tr( "Ignored" ) )
                .arg( tr( "Bookmarked" ) )
                .arg( tr( "Normal" ) )
        );
        
        connect( NetworkManager::instance(), SIGNAL( finished( QNetworkReply* ) ), this, SLOT( networkRequest_finished( QNetworkReply* ) ) );
        connect( NetworkManager::instance(), SIGNAL( imageFinished( QNetworkReply*, const QByteArray&, const QPixmap& ) ), this, SLOT( networkRequest_imageFinished( QNetworkReply*, const QByteArray&, const QPixmap& ) ) );
        connect( model, SIGNAL( requestImageDownload( const QString& ) ), this, SLOT( model_requestImageDownload( const QString& ) ) );
        connect( model, SIGNAL( requestFetchMore() ), this, SLOT( model_requestFetchMore() ) );
        connect( proxy, SIGNAL( rowCountChanged( int ) ), ui->lAnnouncementsNumber, SLOT( setNum( int ) ) );
        connect( ui->pbSearch, SIGNAL( clicked() ), this, SLOT( pbSearch_clicked() ) );
        connect( ui->twPages, SIGNAL( tabCloseRequested( int ) ), this, SLOT( twPages_tabCloseRequested( int ) ) );
        connect( ui->lvAnnouncements->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ), this, SLOT( lvAnnouncements_selectionChanged() ) );
        connect( ui->aSwitchAnnouncementIgnoreState, SIGNAL( triggered( bool ) ), this, SLOT( switchSelectedAnnouncementIgnoreState( bool ) ) );
        connect( ui->aSwitchAnnouncementBookmarkState, SIGNAL( triggered( bool ) ), this, SLOT( switchSelectedAnnouncementBookmarkState( bool ) ) );
        connect( ui->aOpenAnnouncementInNewTab, SIGNAL( triggered() ), this, SLOT( openSelectedAnnouncementInNewTab() ) );
        connect( ui->aOpenAnnouncementInDefaultBrowser, SIGNAL( triggered() ), this, SLOT( openSelectedAnnouncementInDefaultBrowser() ) );
        
        lvAnnouncements_selectionChanged();
    }
    
    ~UIMainPrivate() {
        delete movie;
        delete ui;
    }
    
    void retranslateUi() {
        ui->retranslateUi( widget );
    }
    
    void sendSearchRequest( int page ) {
        AbstractHousingDriver* driver = ui->iswSearch->currentDriver();
        
        if ( !driver ) {
            return;
        }
        
        model->setIgnoredIdSet( ui->iswSearch->ignoredIdSet() );
        model->setBookmarkedIdSet( ui->iswSearch->bookmarkedIdSet() );
        
        if ( TEST_CASE_DEBUG ) {
            Announcement::List announcements;
            AbstractHousingDriver::RequestResultProperties properties;
            const bool ok = driver->parseSearchRequestData( driver->testCase(), announcements, &properties );
            
            model->setCurrentPage( properties.page );
            model->setCanFetchMore( properties.hasNextPage );
            
            if ( ok ) {
                model->setAnnouncements( announcements );
            }
            else {
                qWarning( "%s: Testcase error", Q_FUNC_INFO );
            }
        }
        else {
            const AbstractHousingDriver::RequestProperties properties = ui->iswSearch->requestProperties();
            QNetworkRequest request;
            QByteArray data;
            
            driver->setUpSearchRequest( request, data, properties, page );
            
            if ( data.isEmpty() ) {
                NetworkManager::instance()->get( request );
            }
            else {
                NetworkManager::instance()->post( request, data );
            }
            
            ui->lvAnnouncements->setCornerWidget( movieLabel );
        }
    }
    
    QModelIndex selectedSourceIndex() const {
        return proxy->mapToSource( ui->lvAnnouncements->selectionModel()->selectedIndexes().value( 0 ) );
    }

public slots:
    void  networkRequest_finished( QNetworkReply* reply ) {
        AbstractHousingDriver* driver = ui->iswSearch->currentDriver();
        
        if ( driver && driver->isOwnUrl( reply->request().url() ) ) {
            Announcement::List announcements;
            AbstractHousingDriver::RequestResultProperties properties;
            const bool ok = driver->parseSearchRequestData( reply->readAll(), announcements, &properties );
            
            if ( ok ) {
                model->setCurrentPage( properties.page );
                model->setCanFetchMore( properties.hasNextPage );
                model->addAnnouncements( announcements );
            }
            
            ui->lTotalPagesNumber->setNum( properties.totalPage );
            ui->lFoundNumber->setNum( properties.found );
            ui->lVisibleNumber->setNum( properties.visible );
            ui->lAnnouncementsNumber->setNum( proxy->rowCount() );
        }
        
        ui->lvAnnouncements->setCornerWidget( 0 );
    }
    
    void networkRequest_imageFinished( QNetworkReply* reply, const QByteArray& data, const QPixmap& pixmap ) {
        Q_UNUSED( data );
        
        const QString key = reply->request().url().toString();
        
        if ( !QPixmapCache::insert( key, pixmap ) ) {
            qWarning( "%s: Can not cache pixmap %s", Q_FUNC_INFO, qPrintable( key ) );
        }
        
        model->update();
    }
    
    void model_requestImageDownload( const QString& url ) {
        NetworkManager::instance()->getImage( QNetworkRequest( url ) );
    }
    
    void model_requestFetchMore() {
        sendSearchRequest( model->currentPage() +1 );
    }
    
    void view_loadFinished( bool ok ) {
        Q_UNUSED( ok );
        QWebView* view = qobject_cast<QWebView*>( sender() );
        const int index = ui->twPages->indexOf( view );
        ui->twPages->setTabIcon( index, view->icon() );
        ui->twPages->setTabText( index, view->title() );
        ui->twPages->setTabToolTip( index, view->url().toString() );
    }
    
    void lvAnnouncements_selectionChanged() {
        const QModelIndex index = selectedSourceIndex();
        const QString url = index.data( AnnouncementModel::UrlRole ).toString();
        const int id = index.data( AnnouncementModel::IdRole ).toInt();
        
        ui->aSwitchAnnouncementIgnoreState->setEnabled( index.isValid() );
        ui->aSwitchAnnouncementIgnoreState->setChecked( index.isValid() && ui->iswSearch->isIgnoredId( id ) );
        ui->aSwitchAnnouncementBookmarkState->setEnabled( index.isValid() );
        ui->aSwitchAnnouncementBookmarkState->setChecked( index.isValid() && ui->iswSearch->isBookmarkedId( id ) );
        ui->aOpenAnnouncementInNewTab->setEnabled( index.isValid() );
        ui->aOpenAnnouncementInDefaultBrowser->setEnabled( index.isValid() );
    }
    
    void pbSearch_clicked() {
        model->clear();
        sendSearchRequest( 1 );
    }
    
    void twPages_tabCloseRequested( int index ) {
        QWidget* w = ui->twPages->widget( index );
        
        if ( w == ui->wSearchResults ) {
            return;
        }
        
        if ( w ) {
            w->deleteLater();
        }
    }
    
    void switchSelectedAnnouncementIgnoreState( bool ignore ) {
        const QModelIndex index = selectedSourceIndex();
        const QString url = index.data( AnnouncementModel::UrlRole ).toString();
        const int id = index.data( AnnouncementModel::IdRole ).toInt();
        ui->iswSearch->setIgnoredId( id, ignore );
        model->setIgnoredIdSet( ui->iswSearch->ignoredIdSet() );
        
        if ( ignore && ui->iswSearch->isBookmarkedId( id ) ) {
            ui->aSwitchAnnouncementBookmarkState->trigger();
        }
    }
    
    void switchSelectedAnnouncementBookmarkState( bool bookmark ) {
        const QModelIndex index = selectedSourceIndex();
        const QString url = index.data( AnnouncementModel::UrlRole ).toString();
        const int id = index.data( AnnouncementModel::IdRole ).toInt();
        ui->iswSearch->setBookmarkedId( id, bookmark );
        model->setBookmarkedIdSet( ui->iswSearch->bookmarkedIdSet() );
        
        if ( bookmark && ui->iswSearch->isIgnoredId( id ) ) {
            ui->aSwitchAnnouncementIgnoreState->trigger();
        }
    }
    
    void openSelectedAnnouncementInNewTab() {
        const QModelIndex index = selectedSourceIndex();
        const QString url = index.data( AnnouncementModel::UrlRole ).toString();
        const int id = index.data( AnnouncementModel::IdRole ).toInt();
        
        foreach ( QWebView* view, ui->twPages->findChildren<QWebView*>() ) {
            if ( view->url() == url ) {
                return;
            }
        }
        
        QWebView* view = new QWebView;
        ui->twPages->addTab( view, tr( "Loading %1..." ).arg( id ) );
        connect( view, SIGNAL( loadFinished( bool ) ), this, SLOT( view_loadFinished( bool ) ) );
        view->setUrl( url );
    }
    
    void openSelectedAnnouncementInDefaultBrowser() {
        const QModelIndex index = selectedSourceIndex();
        const QString url = index.data( AnnouncementModel::UrlRole ).toString();
        QDesktopServices::openUrl( url );
    }
};

UIMain::UIMain( QWidget* parent )
    : QMainWindow( parent ),
        d( new UIMainPrivate( this ) )
{
}

UIMain::~UIMain()
{
}

void UIMain::changeEvent( QEvent* event )
{
    QMainWindow::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        d->retranslateUi();
    }
}

void UIMain::showEvent( QShowEvent* event )
{
    QMainWindow::showEvent( event );
    
    const QSettings settings;
    
    restoreGeometry( settings.value( "MainWindow/Geometry" ).toByteArray() );
    restoreState( settings.value( "MainWindow/State" ).toByteArray() );
    d->ui->iswSearch->setCurrentDriverName( settings.value( "MainWindow/CurrentDriverName" ).toString() );
    d->ui->iswSearch->loadRequestProperties();
}

void UIMain::closeEvent( QCloseEvent* event )
{
    const AbstractHousingDriver* driver = d->ui->iswSearch->currentDriver();
    QSettings settings;
    
    settings.setValue( "MainWindow/Geometry", saveGeometry() );
    settings.setValue( "MainWindow/State", saveState() );
    settings.setValue( "MainWindow/CurrentDriverName", driver ? driver->name() : QString::null );
    d->ui->iswSearch->saveRequestProperties();
    
    QMainWindow::closeEvent( event );
}

#include "UIMain.moc"
