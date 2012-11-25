#ifndef UIMAIN_H
#define UIMAIN_H

#include <QMainWindow>

class QEvent;
class UIMainPrivate;

class UIMain : public QMainWindow
{
    Q_OBJECT

public:
    UIMain( QWidget* parent = 0 );
    virtual ~UIMain();
    
protected:
    UIMainPrivate* d;
    
    virtual void changeEvent( QEvent* event );
    virtual void showEvent( QShowEvent* event );
    virtual void closeEvent( QCloseEvent* event );
};

#endif // UIMAIN_H
