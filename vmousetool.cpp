#include "vmousetool.h"
#include "vscene.h"

/**
 * @details Classe qui représente l'outil de sélection. Permet de sélectionner et déplacer les formes.
 */

VMouseTool::VMouseTool()
{


}


void VMouseTool::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    scene->mousePressEventDefault(mouseEvent);
}


void VMouseTool::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    scene->mouseMoveEventDefault(mouseEvent);
}


void VMouseTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, VScene* scene, ToolManager* toolmanager)
{
    scene->mouseReleaseEventDefault(mouseEvent);

}

QString VMouseTool::getID()
{
    return QString("mouseTool");
}
