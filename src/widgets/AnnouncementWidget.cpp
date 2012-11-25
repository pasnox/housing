#include "AnnouncementWidget.h"
#include "ui_AnnouncementWidget.h"
#include "interface/Announcement.h"

#include <QEvent>

AnnouncementWidget::AnnouncementWidget( QWidget* parent )
    : QWidget( parent ), ui( new Ui_AnnouncementWidget )
{
    ui->setupUi( this );
}

AnnouncementWidget::~AnnouncementWidget()
{
    delete ui;
}

void AnnouncementWidget::setAnnouncement( const Announcement& announcement )
{
}

void AnnouncementWidget::retranslateUi()
{
    ui->retranslateUi( this );
    // do your custom retranslate here
}

void AnnouncementWidget::changeEvent( QEvent* event )
{
    QWidget::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        retranslateUi();
    }
}
