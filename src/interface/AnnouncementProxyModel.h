#ifndef ANNOUNCEMENTPROXYMODEL_H
#define ANNOUNCEMENTPROXYMODEL_H

#include <QSortFilterProxyModel>

class AnnouncementProxyModelPrivate;
class AnnouncementModel;
class QAction;

class AnnouncementProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    
public:
    AnnouncementProxyModel( AnnouncementModel* parent );
    virtual ~AnnouncementProxyModel();
    
    QAction* filterAction() const;

protected:
    virtual bool filterAcceptsRow( int sourceRow, const QModelIndex & sourceParent ) const;

private:
    AnnouncementProxyModelPrivate* d;

signals:
    void changed();
    void rowCountChanged( int count );
};

#endif // ANNOUNCEMENTPROXYMODEL_H
