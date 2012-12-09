#ifndef FEEDBACKWIDGET_H
#define FEEDBACKWIDGET_H

#include <QWidget>

class FeedbackWidgetPrivate;
class QEvent;

class FeedbackWidget : public QWidget
{
    Q_OBJECT

public:
    FeedbackWidget( QWidget* parent = 0 );
    virtual ~FeedbackWidget();
    
    void clear();
    bool loadFileName( const QString& fileName );
    bool saveFileName( const QString& fileName ) const;
    
protected:
    FeedbackWidgetPrivate* d;
    
    virtual void changeEvent( QEvent* event );
};

#endif // FEEDBACKWIDGET_H
