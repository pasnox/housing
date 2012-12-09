/****************************************************************************
**
**         Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
** Authors   : Filipe Azevedo aka Nox P@sNox <pasnox@gmail.com>
** Project   : Housing
** FileName  : Feedback.h
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
#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QSharedDataPointer>
#include <QVariant>

class FeedbackPrivate;

class Feedback
{
public:
    typedef QList<Feedback> List;
    
    Feedback( const QVariant& variant = QVariant() );
    Feedback( const QDateTime& dateTime, const QString& text );
    Feedback( const Feedback& other );
    virtual ~Feedback();
    
    virtual Feedback& operator=( const Feedback& other );
    virtual bool operator==( const Feedback& other ) const;
    virtual bool operator<( const Feedback& other ) const;
    
    virtual operator QVariant() const;
    virtual Feedback& operator=( const QVariant& variant );
    virtual bool operator==( const QVariant& variant ) const;
    virtual bool operator<( const QVariant& variant ) const;
    
    virtual bool isNull() const;
    
    void setDateTime( const QDateTime& dateTime );
    QDateTime dateTime() const;
    
    void setMessage( const QString& message );
    QString message() const;

    static QVariantList listToVariantList( const Feedback::List& feedbackList );
    static Feedback::List variantListToList( const QVariantList& variantList );

private:
    QSharedDataPointer<FeedbackPrivate> d;
};

Q_DECLARE_METATYPE( Feedback )

#endif // FEEDBACK_H
