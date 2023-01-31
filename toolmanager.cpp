#include "toolmanager.h"
#include "vrectangletool.h"
#include "vmousetool.h"


ToolManager::ToolManager(QObject *parent)
    : QObject{parent}
{

}



void ToolManager::setRectangleTool()
{
    this->CurrentTool = rectangleTool;
}


void ToolManager::setMouseTool()
{
    this->CurrentTool = mouseTool;
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
