#include "pComboBox.h"

pComboBox::pComboBox( QWidget* parent )
    : QComboBox( parent )
{
}

pComboBox::~pComboBox()
{
}

void pComboBox::hidePopup()
{
    emit popupAboutToHide();
    QComboBox::hidePopup();
}

void pComboBox::showPopup()
{
    emit popupAboutToShow();
    QComboBox::showPopup();
}
