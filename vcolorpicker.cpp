#include "vcolorpicker.h"
#include <QPushButton>

/**
 * @brief VColorPicker::VColorPicker
 * @param parent
 * @details
 * Constructeur de la classe VColorPicker
*/
VColorPicker::VColorPicker() : QPushButton()
{
    setAutoFillBackground(true);
    colorDialog = new QColorDialog();
    setStyleSheet("background-color: rgb(255,255,255);");
}

/**
 * @brief VColorPicker::mouseReleaseEvent
 * @param event
 * @details
 * Slot appelé lors d'un clic sur le bouton
 * Affiche un QColorDialog et change la couleur du bouton
*/
void VColorPicker::mouseReleaseEvent(QMouseEvent *event)
{
    int dialogCode = colorDialog->exec();
    if(dialogCode == QDialog::Accepted) {
        setColor(colorDialog->selectedColor());
        emit sigColorChanged(currentColor);
    }

}


/**
 * @brief VColorPicker::setColor
 * @param col
 * @details
 * Change la couleur du bouton
*/
void VColorPicker::setColor(QColor col)
{
    currentColor = col;
    colorDialog->setCurrentColor(col);
    QString qss = QString("background-color: %1").arg(col.name());
    setStyleSheet(qss);
}
