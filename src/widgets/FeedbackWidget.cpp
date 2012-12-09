#include "FeedbackWidget.h"
#include "ui_FeedbackWidget.h"
#include "FeedbackDialog.h"
#include "interface/FeedbackModel.h"
#include "interface/FeedbackItemDelegate.h"

#include <QEvent>
#include <QDateTime>
#include <QMessageBox>

class FeedbackWidgetPrivate : public QObject {
    Q_OBJECT

public:
    FeedbackWidget* widget;
    Ui_FeedbackWidget* ui;
    FeedbackModel* model;
    
public:
    FeedbackWidgetPrivate( FeedbackWidget* _widget )
        : QObject( _widget ),
            widget( _widget ),
            ui( new Ui_FeedbackWidget ),
            model( new FeedbackModel( this ) )
    {
        ui->setupUi( widget );
        ui->lvFeedbacks->setModel( model );
        ui->lvFeedbacks->setItemDelegate( new FeedbackItemDelegate( ui->lvFeedbacks ) );
        
        updateButtons();
        
        connect( ui->tbFeedbackAdd, SIGNAL( clicked() ), this, SLOT( addFeedback() ) );
        connect( ui->tbFeedbackEdit, SIGNAL( clicked() ), this, SLOT( editFeedback() ) );
        connect( ui->tbFeedbacksRemove, SIGNAL( clicked() ), this, SLOT( removeFeedbacks() ) );
        connect( ui->tbFeedbacksClear, SIGNAL( clicked() ), this, SLOT( clearFeedbacks() ) );
        connect( ui->lvFeedbacks->selectionModel(), SIGNAL( selectionChanged( const QItemSelection&, const QItemSelection& ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( rowsInserted( const QModelIndex&, int, int ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( rowsRemoved( const QModelIndex&, int, int ) ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( layoutChanged() ), this, SLOT( updateButtons() ) );
        connect( model, SIGNAL( modelReset() ), this, SLOT( updateButtons() ) );
    }
    
    ~FeedbackWidgetPrivate() {
        delete ui;
    }
    
    void retranslateUi() {
        ui->retranslateUi( widget );
    }

private slots:
    void addFeedback() {
        FeedbackDialog dlg( Feedback( QDateTime::currentDateTime(), QString::null ), widget );
        
        if ( dlg.exec() == QDialog::Accepted ) {
            const Feedback feedback( dlg.feedback() );
            model->addFeedback( feedback );
            ui->lvFeedbacks->setCurrentIndex( model->modelIndex( feedback ) );
        }
    }
    
    void editFeedback() {
        const QModelIndex index = ui->lvFeedbacks->selectionModel()->selectedIndexes().value( 0 );
        FeedbackDialog dlg( model->feedback( index ), widget );
        
        if ( dlg.exec() == QDialog::Accepted ) {
            model->updateFeedback( index, dlg.feedback() );
        }
    }
    
    void removeFeedbacks() {
        model->removeFeedbacks( ui->lvFeedbacks->selectionModel()->selectedIndexes() );
    }
    
    void clearFeedbacks() {
        const QString title = QString::null;
        const QString message = FeedbackWidget::tr( "Are you sure you want to clear the list ?" );
        const QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No;
        const QMessageBox::StandardButton defaultButton = QMessageBox::No;
        
        if ( QMessageBox::question( widget->window(), title, message, buttons, defaultButton ) == defaultButton ) {
            return;
        }
        
        model->clear();
    }
    
    void updateButtons() {
        const bool hasFeedbacks = model->rowCount() > 0;
        const bool hasSelection = !ui->lvFeedbacks->selectionModel()->selectedIndexes().isEmpty();
        
        ui->tbFeedbackEdit->setEnabled( hasSelection );
        ui->tbFeedbacksRemove->setEnabled( hasSelection );
        ui->tbFeedbacksClear->setEnabled( hasFeedbacks );
    }
};

FeedbackWidget::FeedbackWidget( QWidget* parent )
    : QWidget( parent ),
        d( new FeedbackWidgetPrivate( this ) )
{
}

FeedbackWidget::~FeedbackWidget()
{
}

void FeedbackWidget::changeEvent( QEvent* event )
{
    QWidget::changeEvent( event );
    
    if ( event->type() == QEvent::LanguageChange ) {
        d->retranslateUi();
    }
}

void FeedbackWidget::clear()
{
    d->model->clear();
}

bool FeedbackWidget::loadFileName( const QString& fileName )
{
    return d->model->loadFileName( fileName );
}

bool FeedbackWidget::saveFileName( const QString& fileName ) const
{
    return d->model->saveFileName( fileName );
}

#include "FeedbackWidget.moc"
