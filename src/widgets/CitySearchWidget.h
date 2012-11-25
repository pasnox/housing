#ifndef CITYSEARCHWIDGET_H
#define CITYSEARCHWIDGET_H

#include <QWidget>

#include "interface/City.h"

class QEvent;
class AbstractCityQuery;
class CitySearchWidgetPrivate;

class CitySearchWidget : public QWidget
{
    Q_OBJECT

public:
    CitySearchWidget( QWidget* parent = 0 );
    virtual ~CitySearchWidget();
    
    void setCityQuery( AbstractCityQuery* query );
    AbstractCityQuery* cityQuery() const;
    
    void setCities( const City::List& cities );
    City::List cities() const;
    
    void setCodeVisible( bool visible );
    bool isCodeVisible() const;

protected:
    virtual void changeEvent( QEvent* event );

private:
    CitySearchWidgetPrivate* d;
};

#endif // CITYSEARCHWIDGET_H
