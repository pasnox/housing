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
    
    bool loadData( const QString& filePath );
    bool saveData( const QString& filePath ) const;
    
protected:
    FeedbackWidgetPrivate* d;
    
    virtual void changeEvent( QEvent* event );
};

#endif // FEEDBACKWIDGET_H
