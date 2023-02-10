#include "ellipsetool.h"
#include "vtool.h"
#include <iostream>
#include <toolmanager.h>

ellipseTool::ellipseTool()
{

}

/**
 * @brief ellipseTool::mousePressEvent
 * @param mouseEvent
 * @param scene
 * @param toolmanager
 * @details
 * Slot appelé lors d'un clic sur la scène
 * Crée un nouvel objet ellipse et l'ajoute à la scène
*/
void ellipseTool::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
//    QPointF originePoint = mouseEvent->buttonDownScenePos(Qt::RightButton);
    pBuildingEllipse = new ellipse();
    pBuildingEllipse->setRect(0, 0, 6, 6);
//    pBuildingEllipse->setSelected(true);
    scene->addItem(pBuildingEllipse);
    pBuildingEllipse->setPos( mouseEvent->scenePos().x(), mouseEvent->scenePos().y() );
}

/**
 * @brief ellipseTool::mouseMoveEvent
 * @param mouseEvent
 * @param scene
 * @param toolmanager
 * @details
 * Slot appelé lors d'un déplacement de la souris sur la scène
 * Modifie la taille de l'ellipse en cours de création
*/
void ellipseTool::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    QPointF originePoint = mouseEvent->buttonDownScenePos(Qt::LeftButton);
    int x_top_left = std::min(originePoint.x(), mouseEvent->scenePos().x());
    int y_top_left = std::min(originePoint.y(), mouseEvent->scenePos().y());

    int width = std::abs(mouseEvent->scenePos().x()-originePoint.x());
    int height = std::abs(mouseEvent->scenePos().y()-originePoint.y());

    std::cout << "[LP-DEBUG] width " << originePoint.x()<< std::endl;
    std::cout << "[LP-DEBUG] height " << originePoint.y()<< std::endl;

    pBuildingEllipse->setPos(x_top_left,y_top_left);
    pBuildingEllipse->setRect(0, 0, width, height);
//    pBuildingEllipse->setSelected(true);
    pBuildingEllipse->updateGrabbersPosition();
}

/**
 * @brief ellipseTool::mouseReleaseEvent
 * @param mouseEvent
 * @param scene
 * @param toolmanager
 * @details
 * Slot appelé lors d'un relâchement de la souris sur la scène
 * Change l'outil courant en mouseTool
*/
void ellipseTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    toolmanager->setMouseTool();
}

/**
 * @brief ellipseTool::getID
 * @return
 * @details
 * Retourne l'identifiant de l'outil ellipseTool
*/
QString ellipseTool::getID()
{
    return QString("ellipseTool");
}

