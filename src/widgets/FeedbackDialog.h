#ifndef FEEDBACKDIALOG_H
#define FEEDBACKDIALOG_H

#include <QDialog>

class FeedbackDialogPrivate;
class Feedback;

class FeedbackDialog : public QDialog
{
    Q_OBJECT

public:
    FeedbackDialog( QWidget* parent = 0 );
    FeedbackDialog( const Feedback& feedback, QWidget* parent = 0 );
    virtual ~FeedbackDialog();
    
    void setFeedback( const Feedback& feedback );
    Feedback feedback() const;

public slots:
    virtual void accept();
    
protected:
    FeedbackDialogPrivate* d;
    
    virtual void changeEvent( QEvent* event );
};

#endif // FEEDBACKDIALOG_H
