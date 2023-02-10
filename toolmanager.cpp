#include "toolmanager.h"
#include "vrectangletool.h"
#include "ellipsetool.h"
#include "vmousetool.h"

/**
 * @brief ToolManager::ToolManager
 * @param parent
 * @details
 * Constructeur de la classe ToolManager
*/
ToolManager::ToolManager(QObject *parent)
    : QObject{parent}
{

}


/**
 * @brief ToolManager::setRectangleTool
 * @details
 * Change l'outil courant en rectangleTool
 * Emet un signal sigToolChanged
*/
void ToolManager::setRectangleTool()
{
    this->CurrentTool = rectangleTool;
    sigToolChanged(VRectangleTool::getID());
}

/**
 * @brief ToolManager::setEllipseTool
 * @details
 * Change l'outil courant en ellipseTool
 * Emet un signal sigToolChanged
*/
void ToolManager::setEllipseTool()
{
    this->CurrentTool = ellipsetool;
    sigToolChanged(ellipseTool::getID());
}

/**
 * @brief ToolManager::setMouseTool
 * @details
 * Change l'outil courant en mouseTool
 * Emet un signal sigToolChanged
*/
void ToolManager::setMouseTool()
{
    this->CurrentTool = mouseTool;
    sigToolChanged(VMouseTool::getID());
}

/**
 * @brief ToolManager::slotMousePress
 * @param mouseEvent
 * @param scene
 * @details
 * Slot appelé lors d'un clic sur la scène
 * Appelle la méthode mousePressEvent de l'outil courant
*/
void ToolManager::slotMousePress(QGraphicsSceneMouseEvent *mouseEvent, VScene *scene)
{
    this->CurrentTool->mousePressEvent(mouseEvent, scene, this);
}

/**
 * @brief ToolManager::slotMouseMove
 * @param mouseEvent
 * @param scene
 * @details
 * Slot appelé lors d'un déplacement de la souris sur la scène
 * Appelle la méthode mouseMoveEvent de l'outil courant
*/
void ToolManager::slotMouseMove(QGraphicsSceneMouseEvent *mouseEvent, VScene *scene)
{
    this->CurrentTool->mouseMoveEvent(mouseEvent, scene, this);
}


/**
 * @brief ToolManager::slotMouseRelease
 * @param mouseEvent
 * @param scene
 * @details
 * Slot appelé lors d'un relâchement de la souris sur la scène
 * Appelle la méthode mouseReleaseEvent de l'outil courant
*/
void ToolManager::slotMouseRelease(QGraphicsSceneMouseEvent *mouseEvent, VScene *scene)
{
    this->CurrentTool->mouseReleaseEvent(mouseEvent, scene, this);
}
