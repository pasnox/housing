#include "FeedbackDialog.h"
#include "ui_FeedbackDialog.h"
#include "interface/Feedback.h"

#include <QEvent>
#include <QMessageBox>

class FeedbackDialogPrivate : public QObject {
    Q_OBJECT

public:
    FeedbackDialog* widget;
    Ui_FeedbackDialog* ui;
    
public:
    FeedbackDialogPrivate( FeedbackDialog* _widget )
        : QObject( _widget ),
            widget( _widget ),
            ui( new Ui_FeedbackDialog )
    {
        ui->setupUi( widget );
    }
    
    ~FeedbackDialogPrivate() {
        delete ui;
    }

public slots:
    void retranslateUi() {
        ui->retranslateUi( widget );
    }
};

FeedbackDialog::FeedbackDialog( QWidget* parent )
    : QDialog( parent ),
        d( new FeedbackDialogPrivate( this ) )
{
}

FeedbackDialog::FeedbackDialog( const Feedback& feedback, QWidget* parent )
    : QDialog( parent ),
        d( new FeedbackDialogPrivate( this ) )
{
    setFeedback( feedback );
}

FeedbackDialog::~FeedbackDialog()
{
}

void FeedbackDialog::setFeedback( const Feedback& feedback )
{
    d->ui->dteDateTime->setDateTime( feedback.dateTime() );
    d->ui->pteMessage->setPlainText( feedback.message() );
}

Feedback FeedbackDialog::feedback() const
{
    return Feedback( d->ui->dteDateTime->dateTime(), d->ui->pteMessage->toPlainText() );
}

void FeedbackDialog::accept()
{
    if ( d->ui->pteMessage->toPlainText().isEmpty() ) {
        QMessageBox::information( this, QString::null, tr( "The message can't be empty." ) );
        return;
    }
    
    QDialog::accept();
}

void FeedbackDialog::changeEvent( QEvent* event )
{
    QDialog::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        d->retranslateUi();
    }
}

#include "FeedbackDialog.moc"
