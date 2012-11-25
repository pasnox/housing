#ifndef SELOGERCITYQUERY_H
#define SELOGERCITYQUERY_H

#include "interface/AbstractCityQuery.h"

class SeLogerCityQueryPrivate;

class SeLogerCityQuery : public AbstractCityQuery
{
    Q_OBJECT
    
public:
    SeLogerCityQuery( QObject* parent = 0 );
    virtual ~SeLogerCityQuery();

    virtual void setMinimumSearchLength( int length );
    virtual int minimumSearchLength() const;

public slots: 
    virtual void search( const QString& text );

private:
    SeLogerCityQueryPrivate* d;
};

#endif // SELOGERCITYQUERY_H
