#include "vverticallayout.h"
#include "vshape.h"
#include <QWidget>
#include <iostream>

VVerticalLayout::VVerticalLayout() : QVBoxLayout()
{
}


void VVerticalLayout::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}



void VVerticalLayout::refresh(VShape* selectedShape, QWidget* panel)
{

    //TODO parent pout panel

    clearLayout(this);

    if(selectedShape==NULL){
        std::cout << "pas de shape selected: " << std::endl;
        panel->setVisible(false);
        return;
    }else{
        QLayout* shapePanel = selectedShape->getPanel();
        this->addLayout(shapePanel);
        panel->setVisible(true);
    }


}

