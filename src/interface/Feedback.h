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
