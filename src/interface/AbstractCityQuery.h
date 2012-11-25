#ifndef ABSTRACTCITYQUERY_H
#define ABSTRACTCITYQUERY_H

#include <QObject>

#include "City.h"

class AbstractCityQuery : public QObject
{
    Q_OBJECT
    
public:
    AbstractCityQuery( QObject* parent = 0 );
    virtual ~AbstractCityQuery();

    virtual void setMinimumSearchLength( int length ) = 0;
    virtual int minimumSearchLength() const = 0;

public slots: 
    virtual void search( const QString& text ) = 0;

signals:
    void citiesReceived( const City::List& cities );
    void error( const QString& error );
};

#endif // ABSTRACTCITYQUERY_H
