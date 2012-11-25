#ifndef ANNOUNCEMENTWIDGET_H
#define ANNOUNCEMENTWIDGET_H

#include <QWidget>

class Ui_AnnouncementWidget;
class QEvent;
class Announcement;

class AnnouncementWidget : public QWidget
{
    Q_OBJECT

public:
    AnnouncementWidget( QWidget* parent = 0 );
    virtual ~AnnouncementWidget();
    
    void setAnnouncement( const Announcement& announcement );

public slots:
    virtual void retranslateUi();
    
protected:
    Ui_AnnouncementWidget* ui;
    
    virtual void changeEvent( QEvent* event );
};

#endif // ANNOUNCEMENTWIDGET_H
