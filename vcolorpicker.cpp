#include "vcolorpicker.h"
#include <QPushButton>

VColorPicker::VColorPicker() : QPushButton()
{
    setAutoFillBackground(true);
    colorDialog = new QColorDialog();
    setStyleSheet("background-color: rgb(255,255,255);");
}

void VColorPicker::mouseReleaseEvent(QMouseEvent *event)
{
    int dialogCode = colorDialog->exec();
    if(dialogCode == QDialog::Accepted) {
        setColor(colorDialog->selectedColor());
        emit sigColorChanged(currentColor);
    }

}



void VColorPicker::setColor(QColor col)
{
    currentColor = col;
    colorDialog->setCurrentColor(col);
    QString qss = QString("background-color: %1").arg(col.name());
    setStyleSheet(qss);
}
