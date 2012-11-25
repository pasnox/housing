#ifndef CITYMODEL_H
#define CITYMODEL_H

#include <QAbstractTableModel>

#include "City.h"

class CityModelPrivate;

class CityModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    enum CustomRoles {
        LabelRole = Qt::UserRole,
        ValueRole,
        CodeRole,
        // internal, do not use
        FirstRole = LabelRole,
        LastRole = CodeRole
    };
    
    CityModel( QObject* parent = 0 );
    virtual ~CityModel();
    
    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    
    void clear();
    
    void setCities( const City::List& cities );
    City::List cities() const;
    
    void addCity( const City& city );
    City city( const QModelIndex& index ) const;
    void removeCities( const QModelIndexList& indexes );
    
    void setCodeVisible( bool visible );
    bool isCodeVisible() const;

private:
    CityModelPrivate* d;
};

#endif // CITYMODEL_H
