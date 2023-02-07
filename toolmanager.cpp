#include "toolmanager.h"
#include "vrectangletool.h"
#include "ellipsetool.h"
#include "vmousetool.h"


ToolManager::ToolManager(QObject *parent)
    : QObject{parent}
{

}



void ToolManager::setRectangleTool()
{
    this->CurrentTool = rectangleTool;
    sigToolChanged(VRectangleTool::getID());
}

void ToolManager::setEllipseTool()
{
    this->CurrentTool = ellipsetool;
    sigToolChanged(ellipseTool::getID());
}


void ToolManager::setMouseTool()
{
    this->CurrentTool = mouseTool;
    sigToolChanged(VMouseTool::getID());
}


void ToolManager::slotMousePress(QGraphicsSceneMouseEvent *mouseEvent, VScene *scene)
{
    this->CurrentTool->mousePressEvent(mouseEvent, scene, this);
}

void ToolManager::slotMouseMove(QGraphicsSceneMouseEvent *mouseEvent, VScene *scene)
{
    this->CurrentTool->mouseMoveEvent(mouseEvent, scene, this);
}

void ToolManager::slotMouseRelease(QGraphicsSceneMouseEvent *mouseEvent, VScene *scene)
{
    this->CurrentTool->mouseReleaseEvent(mouseEvent, scene, this);
}
