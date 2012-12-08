/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : FeedbackModel.h
** Date      : 2012-12-02T21:57:14
** License   : GPL3
** Home Page : https://github.com/pasnox/housing
** Comment   : An application to search for rent / purchase of appartment / house.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This package is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#ifndef FEEDBACKMODEL_H
#define FEEDBACKMODEL_H

#include <QAbstractTableModel>

#include "Feedback.h"

class FeedbackModelPrivate;

class FeedbackModel : public QAbstractTableModel
{
    Q_OBJECT
    
public:
    enum CustomRoles {
        DateTimeRole = Qt::UserRole,
        MessageRole,
        FeedbackRole
    };
    
    FeedbackModel( QObject* parent = 0 );
    virtual ~FeedbackModel();
    
    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    virtual void sort( int column, Qt::SortOrder order = Qt::AscendingOrder );
    
    void clear();
    void addFeedbacks( const Feedback::List& feedbacks );
    void addFeedback( const Feedback& feedback );
    void setFeedbacks( const Feedback::List& feedbacks );
    void updateFeedback( const QModelIndex& index, const Feedback& feedback );
    void removeFeedbacks( const QModelIndexList& indexes );
    void removeFeedback( const QModelIndex& index );
    Feedback::List feedbacks() const;
    Feedback feedback( const QModelIndex& index ) const;
    QModelIndex modelIndex( const Feedback& feedback, int column = 0 ) const;
    
    bool loadData( const QString& filePath );
    bool saveData( const QString& filePath ) const;

public slots:
    void update();

private:
    FeedbackModelPrivate* d;
};

#endif // FEEDBACKMODEL_H
