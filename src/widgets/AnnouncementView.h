#ifndef ANNOUNCEMENTVIEW_H
#define ANNOUNCEMENTVIEW_H

#include <QListView>

class AnnouncementViewPrivate;
class QHeaderView;

class AnnouncementView : public QListView
{
    Q_OBJECT
    
public:
    AnnouncementView( QWidget* parent = 0 );
    virtual ~AnnouncementView();
    
    QHeaderView* header() const;

public slots:
    virtual void setModel( QAbstractItemModel* model );

protected:
    virtual void resizeEvent( QResizeEvent* event );
    
private:
    AnnouncementViewPrivate* d;
};

#endif // ANNOUNCEMENTVIEW_H
