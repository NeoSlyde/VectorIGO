#include "vverticallayout.h"
#include "vshape.h"
#include <QWidget>
#include <iostream>

/**
 * @details Permet de gérer le panneau propre à chaque forme sur la droite.
 */

VVerticalLayout::VVerticalLayout() : QVBoxLayout()
{
}


/**
 * @brief VVerticalLayout::clearLayout
 * @param layout 
 * @param deleteWidgets 
 * @details Permet de retirer de l'affichage le panneau.
 */
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


/**
 * @brief VVerticalLayout::refresh
 * @param selectedShape 
 * @param panel 
 * @details Permet de rafraichir le panneau en fonction de la forme actuelle.
 */
void VVerticalLayout::refresh(VShape* selectedShape, QWidget* panel)
{

    //TODO parent pout panel

    clearLayout(this);

    if(selectedShape==NULL){
        std::cout << "pas de shape selected: " << std::endl;
        panel->setVisible(false);
        return;
    }else{
        selectedShape->Accept(&panelVisitor);
        QLayout* shapePanel = panelVisitor.getResult();
        this->addLayout(shapePanel);
        panel->setVisible(true);
    }


}

