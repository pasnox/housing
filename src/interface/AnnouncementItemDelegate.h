#ifndef ANNOUNCEMENTITEMDELEGATE_H
#define ANNOUNCEMENTITEMDELEGATE_H

#include <QStyledItemDelegate>

class AnnouncementItemDelegatePrivate;
class QAbstractItemView;

class AnnouncementItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    
public:
    AnnouncementItemDelegate( QAbstractItemView* parent );
    virtual ~AnnouncementItemDelegate();
    
    virtual QString displayText( const QVariant& value, const QLocale& locale ) const;
    virtual void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
    virtual QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const;

private:
    AnnouncementItemDelegatePrivate* d;
};

#endif // ANNOUNCEMENTITEMDELEGATE_H
