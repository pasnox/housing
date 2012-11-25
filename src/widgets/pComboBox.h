#ifndef PCOMBOBOX_H
#define PCOMBOBOX_H

#include <QComboBox>

class pComboBox : public QComboBox
{
    Q_OBJECT
    
public:
    pComboBox( QWidget* parent = 0 );
    virtual ~pComboBox();

    virtual void hidePopup();
    virtual void showPopup();

signals:
    void popupAboutToHide();
    void popupAboutToShow();
};

#endif // PCOMBOBOX_H
