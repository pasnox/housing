#ifndef INPUTSEARCHWIDGET_H
#define INPUTSEARCHWIDGET_H

#include <QScrollArea>
#include <QSet>

#include "interface/AbstractHousingDriver.h"

class InputSearchWidgetPrivate;
class QEvent;

class InputSearchWidget : public QScrollArea
{
    Q_OBJECT

public:
    InputSearchWidget( QWidget* parent = 0 );
    virtual ~InputSearchWidget();
    
    void setCurrentDriver( AbstractHousingDriver* driver );
    AbstractHousingDriver* currentDriver() const;
    
    void setCurrentDriverName( const QString& name );
    QString currentDriverName() const;
    
    void setIgnoredId( int id, bool ignored );
    bool isIgnoredId( int id ) const;
    QSet<int> ignoredIdSet() const;
    
    void setBookmarkedId( int id, bool ignored );
    bool isBookmarkedId( int id ) const;
    QSet<int> bookmarkedIdSet() const;
    
    void setRequestProperties( const AbstractHousingDriver::RequestProperties& properties );
    AbstractHousingDriver::RequestProperties requestProperties() const;
    
    bool loadRequestProperties();
    bool saveRequestProperties() const;
    
protected:
    virtual void changeEvent( QEvent* event );

private:
    InputSearchWidgetPrivate* d;
};

#endif // INPUTSEARCHWIDGET_H
