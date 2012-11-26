#ifndef CITYCOMBOBOX_H
#define CITYCOMBOBOX_H

#include "FreshGui/pComboBox"

#include "interface/City.h"

class CityComboBoxPrivate;
class AbstractCityQuery;

class CityComboBox : public pComboBox
{
    Q_OBJECT
    
public:
    CityComboBox( QWidget* parent = 0 );
    virtual ~CityComboBox();
    
    void setCityQuery( AbstractCityQuery* query );
    AbstractCityQuery* cityQuery() const;
    
    City city() const;

private:
    CityComboBoxPrivate* d;
};

#endif // CITYCOMBOBOX_H
